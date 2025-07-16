local heap = {}
local metatable = { __index = heap }

function heap.less_than(a, b)
	return a < b
end

function heap:_swap(i, j)
	self[i], self[j] = self[j], self[i]
end

function heap:_insert(val)
	table.insert(self, val)
end

function heap:_remove()
	return table.remove(self)
end

function heap:_heapify_down(index)
	local left_child = index * 2
	if left_child > #self then
		return
	end
	local smallest_child = left_child + 1
	if smallest_child > #self or self.less_than(self[left_child], self[smallest_child]) then
		smallest_child = left_child
	end
	if self.less_than(self[smallest_child], self[index]) then
		self:_swap(index, smallest_child)
		return self:_heapify_down(smallest_child)
	end
end

function heap:_heapify_up(index)
	if index == 1 then
		return
	end
	local parent = math.floor(index / 2)
	if self.less_than(self[index], self[parent]) then
		self:_swap(index, parent)
		return self:_heapify_up(parent)
	end
end

function heap.new(
	self,
	less_than
)
	self = setmetatable(self or {}, metatable)
	self.less_than = less_than
	for i = math.floor(#self / 2), 1, -1 do
		self:_heapify_down(i)
	end
	return self
end

function heap:empty()
	return self[1] == nil
end

function heap:size()
	return #self
end

function heap:push(value)
	self:_insert(value)
	self:_heapify_up(#self)
end

function heap:top()
	return self[1]
end

function heap:pop()
	self:_swap(1, #self)
	local value = self:_remove()
	if not self:empty() then
		self:_heapify_down(1)
	end
	return value
end

return heap
