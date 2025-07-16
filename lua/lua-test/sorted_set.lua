


local sorted_set = {}

function sorted_set.less_than(a, b)
	return a < b
end























function sorted_set:has(key)
	return self:find(key) ~= nil
end




















































local function setop(
	self,
	other,
	add_self,
	add_common,
	add_other
)
	assert(self.less_than == other.less_than, "inequal orderings")
	local less_than = self.less_than

	local next_self = self:ascending()
	local next_other = other:ascending()
	local elems = {}
	local elem_self, elem_other = next_self(), next_other()
	while elem_self ~= nil and elem_other ~= nil do
		if less_than(elem_self, elem_other) then
			if add_self then
				table.insert(elems, elem_self)
			end
			elem_self = next_self()
		elseif less_than(elem_other, elem_self) then
			if add_other then
				table.insert(elems, elem_other)
			end
			elem_other = next_other()
		else
			if add_common then
				table.insert(elems, elem_self)
			end
			elem_self, elem_other = next_self(), next_other()
		end
	end
	if add_self then
		while elem_self ~= nil do
			table.insert(elems, elem_self)
			elem_self = next_self()
		end
	end
	if add_other then
		while elem_other ~= nil do
			table.insert(elems, elem_other)
			elem_other = next_other()
		end
	end
	return self.new(elems)
end


function sorted_set:union(other)
	return setop(self, other, true, true, true)
end


function sorted_set:difference(other)
	return setop(self, other, true, false, false)
end


function sorted_set:symmetric_difference(other)
	return setop(self, other, true, false, true)
end


function sorted_set:intersection(other)
	return setop(self, other, false, true, false)
end

return sorted_set
