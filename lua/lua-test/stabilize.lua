
return function(
	sort
)

	return function(list, less_than)
		less_than = less_than or function(a, b)
			return a < b
		end

		local indices = {}
		for index = 1, #list do
			indices[index] = index
		end

		sort(indices, function(index_a, index_b)
			if less_than(list[index_a], list[index_b]) then
				return true
			end
			if less_than(list[index_b], list[index_a]) then
				return false
			end
			return index_a < index_b
		end)

		for index = 1, #list do
			indices[index] = list[indices[index]]
		end

		for index = 1, #list do
			list[index] = indices[index]
		end
	end
end
