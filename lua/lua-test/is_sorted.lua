return function(
	list,

	less_than
)
	less_than = less_than or function(a, b)
		return a < b
	end
	for i = 2, #list do



		if less_than(list[i], list[i - 1]) then

			return false
		end
	end

	return true
end
