


local choiceset = {}

choiceset.random = math.random

function choiceset.new(


	random
)
	return { random = random, idx = {} }
end

function choiceset:add(element)
	if self.idx[element] then
		return
	end
	self[#self + 1] = element
	self.idx[element] = #self
	return true
end

function choiceset:has(element)
	return not not self.idx[element]
end

function choiceset:remove(element)
	local idx = self.idx[element]
	if not idx then
		return
	end

	local last_element = self[#self]
	self[idx] = last_element
	self.idx[last_element] = idx

	self[#self] = nil
	self.idx[element] = nil
	return true
end

function choiceset:choose()

	return self[self.random(#self)]
end

local function next_key(table, key)
	return (next(table, key))
end

function choiceset:elements()
	return next_key, self.idx, nil
end

return require("class")(choiceset)
