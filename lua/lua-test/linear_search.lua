return function(
	list,

	value,

	sorted,

	less_than
)
	less_than = less_than or function(a, b)
		return a < b
	end
	for index, element in ipairs(list) do
		if less_than(value, element) then
			if sorted then

				return -index
			end
		elseif not less_than(element, value) then

			return index
		end
	end


	return -#list - 1
end
