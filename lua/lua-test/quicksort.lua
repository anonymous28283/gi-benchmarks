local three_way_partition = require("sorting.three_way_partition")

return function(

	choose_pivot
)
	choose_pivot = choose_pivot or math.random
	return function(

		list,

		less_than
	)
		less_than = less_than or function(a, b)
			return a < b
		end
		local function quicksort(from, to)
			if from >= to then
				return
			end





			local pivot_val = list[choose_pivot(from, to)]
			local smaller_to, larger_from = three_way_partition(list, from, to, pivot_val, less_than)

			if smaller_to - from < to - larger_from then
				quicksort(from, smaller_to)
				return quicksort(larger_from, to)
			end
			quicksort(larger_from, to)
			return quicksort(from, smaller_to)
		end
		quicksort(1, #list)
	end
end
