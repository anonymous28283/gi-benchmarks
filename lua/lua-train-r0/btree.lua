



local binary_search = require("searches.binary_search")

local btree = {}
local metatable = { __index = btree }






btree.order = 255





local function slice(t, from, to)
	local res = {}
	local j = from
	for i = 1, to - from + 1 do
		res[i] = t[j]
		j = j + 1
	end
	return res
end

local function list_copy(t)
	local copy = {}
	for i = 1, #t do
		copy[i] = t[i]
	end
	return copy
end


local function table_append_all(dst, src)
	for _, v in ipairs(src) do
		table.insert(dst, v)
	end
end

function btree.new(keys, less_than)

	keys = keys or {}

	local max_keys = 2 * btree.order - 1
	local children
	while #keys > max_keys do
		local next_keys, next_children = {}, {}
		local key_idx, child_idx = 1, 1
		local rem_keys = #keys
		local function add_child(n_keys)
			assert(n_keys > 0)
			local new_key_idx, new_child_idx = key_idx + n_keys - 1, child_idx + n_keys
			table.insert(next_children, {
				keys = slice(keys, key_idx, new_key_idx),
				children = children and slice(children, child_idx, new_child_idx),
			})
			new_key_idx = new_key_idx + 1
			if keys[new_key_idx] then
				table.insert(next_keys, keys[new_key_idx])
				new_key_idx = new_key_idx + 1
				rem_keys = rem_keys - 1
			end
			key_idx, child_idx = new_key_idx, new_child_idx + 1
			rem_keys = rem_keys - n_keys
		end
		while rem_keys > 2 * max_keys do
			add_child(max_keys)
		end


		add_child(math.floor(rem_keys / 2))
		add_child(rem_keys)
		assert(rem_keys == 0)
		keys, children = next_keys, next_children
	end
	return setmetatable({
		_root = {
			keys = keys,
			children = children,
		},
		less_than = less_than,
	}, metatable)
end

function btree:empty()
	return self._root.keys[1] == nil
end

function btree:clear()
	self._root = { keys = {} }
end

function btree:copy()
	local function copy(node)

		local res = { keys = list_copy(node.keys) }

		if node.children then
			local children = {}
			for i, child in ipairs(node.children) do
				children[i] = copy(child)
			end
			res.children = children
		end
		return res
	end

	return setmetatable({
		_root = copy(self._root),

		less_than = rawget(self, "less_than"),
	}, getmetatable(self))
end

function btree:find(key)
	local less_than = self.less_than
	local node = self._root
	repeat
		local i = binary_search(node.keys, key, less_than)
		if i > 0 then
			return node.keys[i]
		end

		node = node.children and node.children[-i]
	until not node
	return nil
end

local function min(node)
	while node.children do
		node = node.children[1]
	end
	return node.keys[1]
end

function btree:min()
	return min(self._root)
end

local function max(node)
	while node.children do
		node = node.children[#node.children]
	end
	return node.keys[#node.keys]
end

function btree:max()
	return max(self._root)
end

function btree:succ(key)
	if key == nil then
		return self:min()
	end
	local less_than = self.less_than
	local function succ(node)
		local keys, children = node.keys, node.children
		local i = binary_search(keys, key, less_than)
		if not children then
			return keys[i > 0 and (i + 1) or -i]
		end
		if i > 0 then
			return min(children[i + 1])
		end
		i = -i
		local got = succ(children[i])
		if got ~= nil then
			return got
		end
		return keys[i]
	end
	return succ(self._root)
end

function btree:pred(key)
	if key == nil then
		return self:max()
	end
	local less_than = self.less_than
	local function pred(node)
		local keys, children = node.keys, node.children
		local i = binary_search(keys, key, less_than)
		if not children then
			return keys[math.abs(i) - 1]
		end
		if i > 0 then
			return max(children[i])
		end
		i = -i
		local got = pred(children[i])
		if got ~= nil then
			return got
		end
		return keys[i - 1]
	end
	return pred(self._root)
end

function btree:range_ascending(min_key, max_key)
	if min_key == nil and max_key == nil then
		return self:ascending()
	end
	local less_than = self.less_than
	if min_key ~= nil and max_key ~= nil and less_than(max_key, min_key) then
		return function()
			return nil
		end
	end

	local max_node, max_i
	if max_key ~= nil then
		max_node = self._root
		while true do
			max_i = binary_search(max_node.keys, max_key, less_than)
			if max_i > 0 then
				break
			end
			max_i = -max_i
			if max_node.children then
				max_node = assert(max_node.children[max_i])
			else
				max_i = max_i - 1
				break
			end
		end
	end
	local function iter(
		node,
		border
	)
		local i
		if border then
			i = binary_search(node.keys, min_key, less_than)
			if i > 0 then
				coroutine.yield(node.keys[i])
				i = i + 1
				border = false
			else
				i = -i
			end
		else
			i = 1
		end

		local to_i = node == max_node and max_i or #node.keys
		local children = node.children
		for j = i, to_i do
			if children and iter(children[j], border and j == i) then
				return true
			end
			coroutine.yield(node.keys[j])
		end
		if node == max_node then
			return true
		end
		if children then
			return iter(children[#children], border and i == #children)
		end
	end
	return coroutine.wrap(function()
		iter(self._root, min_key ~= nil)
	end)
end


function btree:range_descending(min_key, max_key)
	if min_key == nil and max_key == nil then
		return self:descending()
	end
	local less_than = self.less_than
	if min_key ~= nil and max_key ~= nil and less_than(max_key, min_key) then
		return function()
			return nil
		end
	end

	local min_node, min_i
	if min_key ~= nil then
		min_node = self._root
		while true do
			min_i = binary_search(min_node.keys, min_key, less_than)
			if min_i > 0 then
				break
			end
			min_i = -min_i
			if min_node.children then
				min_node = assert(min_node.children[min_i])
			else
				break
			end
		end
	end
	local function iter(node, border)
		local i
		if border then
			i = binary_search(node.keys, max_key, less_than)
			if i > 0 then
				coroutine.yield(node.keys[i])
				i = i - 1
				border = false
			else
				i = -i - 1
			end
		else
			i = #node.keys
		end

		local to_i = node == min_node and min_i or 1
		local children = node.children
		for j = i, to_i, -1 do
			if children and iter(children[j + 1], border and j == i) then
				return true
			end
			coroutine.yield(node.keys[j])
		end
		if node == min_node then
			return true
		end
		if children then
			return iter(children[1], border and i == 0)
		end
	end
	return coroutine.wrap(function()
		iter(self._root, max_key ~= nil)
	end)
end

function btree:ascending()
	local function inorder_ascending(node)
		for i = 1, #node.keys do
			if node.children then
				inorder_ascending(node.children[i])
			end
			coroutine.yield(node.keys[i])
		end
		if node.children then
			return inorder_ascending(node.children[#node.children])
		end
	end
	return coroutine.wrap(function()
		inorder_ascending(self._root)
	end)
end

function btree:descending()
	local function inorder_descending(node)
		for i = #node.keys, 1, -1 do
			if node.children then
				inorder_descending(node.children[i + 1])
			end
			coroutine.yield(node.keys[i])
		end
		if node.children then
			return inorder_descending(node.children[1])
		end
	end
	return coroutine.wrap(function()
		inorder_descending(self._root)
	end)
end

function btree:insert(key, upsert)
	local order = self.order
	local mid = order
	local max_keys = 2 * order - 1
	local less_than = self.less_than
	local previous_key






	local function split(node)
		local keys, children = node.keys, node.children
		local low, high = {}, {}
		local pivot
		low.keys, pivot, high.keys = slice(keys, 1, mid - 1), keys[mid], slice(keys, mid + 1, #keys)
		if children then
			low.children, high.children = slice(children, 1, mid), slice(children, mid + 1, #children)
		end
		return low, pivot, high
	end

	local function insert(node)
		local i = binary_search(node.keys, key, less_than)
		if i > 0 then
			previous_key = node.keys[i]
			if upsert then
				node.keys[i] = key
			end
			return
		end
		i = -i
		if node.children then
			local low_child, pivot, high_child = insert(node.children[i])
			if pivot then
				table.insert(node.keys, i, pivot)
				node.children[i] = low_child
				table.insert(node.children, i + 1, high_child)
			end
		else
			table.insert(node.keys, i, key)
		end
		if #node.keys > max_keys then
			return split(node)
		end
	end
	local low_child, pivot, high_child = insert(self._root)
	if pivot then
		self._root = {
			keys = { pivot },
			children = { low_child, high_child },
		}
	end
	return previous_key
end

function btree:remove(key)
	local order, less_than = self.order, self.less_than
	local min_keys = order - 1
	local found


	local function merge(node, i)
		local low_node, pivot, high_node = node.children[i], node.keys[i], node.children[i + 1]
		table.insert(low_node.keys, pivot)
		table_append_all(low_node.keys, high_node.keys)
		if low_node.children then
			table_append_all(low_node.children, assert(high_node.children))
		else
			assert(not high_node.children)
		end

		table.remove(node.keys, i)
		table.remove(node.children, i + 1)
	end


	local function repair(node, i)
		local child = node.children[i]

		local low_sibling = node.children[i - 1]
		if low_sibling and #low_sibling.keys > min_keys then

			table.insert(child.keys, 1, node.keys[i - 1])
			node.keys[i - 1] = table.remove(low_sibling.keys)
			if child.children then
				table.insert(child.children, 1, table.remove(low_sibling.children))
			end
			return
		end
		local high_sibling = node.children[i + 1]
		if high_sibling and #high_sibling.keys > min_keys then
			table.insert(child.keys, node.keys[i])
			node.keys[i] = table.remove(high_sibling.keys, 1)
			if child.children then
				table.insert(child.children, table.remove(high_sibling.children, 1))
			end
			return
		end

		if low_sibling then
			merge(node, i - 1)
		else
			assert(high_sibling)
			merge(node, i)
		end
		return #node.keys < min_keys
	end
	local function delete_from(node)
		local i = binary_search(node.keys, key, less_than)
		if i > 0 then
			found = node.keys[i]
			if node.children then


				local function delete_largest_key(descendant)
					if descendant.children then
						local j = #descendant.children
						return delete_largest_key(descendant.children[j]) and repair(descendant, j)
					else
						node.keys[i] = table.remove(descendant.keys)
						return #descendant.keys < min_keys
					end
				end
				return delete_largest_key(node.children[i]) and repair(node, i)
			else
				table.remove(node.keys, i)
				return #node.keys < min_keys
			end
		elseif node.children then
			assert(#node.children == #node.keys + 1)
			i = -i
			if delete_from(node.children[i]) then
				return repair(node, i)
			end
		end
	end

	if delete_from(self._root) and #self._root.keys == 0 then

		if self._root.children then
			local only_child = self._root.children[1]
			self._root = only_child
		end
	end
	return found
end

return require("class")(btree, require("data_structures.sorted_set.sorted_set"))
