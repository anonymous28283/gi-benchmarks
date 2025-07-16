
return function(

	list,

	less_than
)
	less_than = less_than or function(a, b)
		return a < b
	end
	for index = 2, #list do
		local value = list[index]


		local insertion_index = 1
		while less_than(list[insertion_index], value) and insertion_index < #list do
			insertion_index = insertion_index + 1
		end

		for shift_index = index - 1, insertion_index, -1 do
			list[shift_index + 1] = list[shift_index]
		end
		list[insertion_index] = value
	end
end
