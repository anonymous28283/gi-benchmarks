
return function(

	list,

	less_than
)
	less_than = less_than or function(a, b)
		return a < b
	end
	for _ = 1, #list do
		for next = 2, #list do
			local previous = next - 1
			if less_than(list[next], list[previous]) then
				list[next], list[previous] = list[previous], list[next]
			end
		end
	end
end
