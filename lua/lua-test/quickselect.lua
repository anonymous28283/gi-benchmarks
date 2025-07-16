local three_way_partition = require("sorting.three_way_partition")


return function(



	choose_pivot_builder
)
	choose_pivot_builder = choose_pivot_builder or function()
		return math.random
	end

	return function(

		arr,

		sort_idx,

		less_than,

		from,

		to
	)
		less_than = less_than or function(a, b)
			return a < b
		end
		from, to = from or 1, to or #arr
		assert(sort_idx >= 1 and sort_idx <= #arr and sort_idx == math.floor(sort_idx), "invalid index")
		local choose_pivot
		local function quickselect(from, to, sort_idx)
			if from == to then
				assert(sort_idx == 1)
				return from
			end




			local pivot_val = arr[choose_pivot(from, to)]
			local smaller_to, larger_from = three_way_partition(arr, from, to, pivot_val, less_than)

			local abs_idx = sort_idx + from - 1

			if abs_idx <= smaller_to then
				return quickselect(from, smaller_to, sort_idx)
			end
			if abs_idx < larger_from then
				return abs_idx
			end

			local leq_count = larger_from - from
			return quickselect(larger_from, to, sort_idx - leq_count)
		end
		choose_pivot = choose_pivot_builder(arr, less_than, quickselect)
		return quickselect(from, to, sort_idx)
	end
end
