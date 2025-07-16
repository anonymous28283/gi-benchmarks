return function(
	list,

	value,

	less_than
)
	less_than = less_than or function(a, b)
		return a < b
	end
	local min, max = 1, #list
	while min <= max do
		local pivot = min + math.floor((max - min) / 2)
		local element = list[pivot]
		if less_than(value, element) then
			max = pivot - 1
		elseif less_than(element, value) then
			min = pivot + 1
		else

			return pivot
		end
	end

	return -min
end
