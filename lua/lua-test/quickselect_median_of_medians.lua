local quickselect_builder = require("sorting.quickselect")


return quickselect_builder(function(arr, less_than, quickselect)

	local function partition_5(from, to)

		local mid = math.floor((from + to) / 2)
		for i = from, mid do
			local min_idx, min_val = i, arr[i]
			for j = i + 1, to do
				if less_than(arr[j], min_val) then
					min_idx, min_val = j, arr[j]
				end
			end
			arr[i], arr[min_idx] = arr[min_idx], arr[i]
		end
		return mid
	end

	return function(from, to)
		if to - from < 5 then
			return partition_5(from, to)
		end
		local medians_to = from
		for i = from, to - 4, 5 do
			local median_5 = partition_5(i, i + 4)

			arr[median_5], arr[medians_to] = arr[medians_to], arr[median_5]

			medians_to = medians_to + 1
		end
		local rem = (from - to + 1) % 5
		if rem == 0 then
			medians_to = medians_to - 1
		else
			local median_rem = partition_5(to - rem + 1, to)

			arr[median_rem], arr[medians_to] = arr[medians_to], arr[median_rem]
		end
		local medians_cnt = medians_to - from + 1
		local median_sorted_idx = math.ceil(medians_cnt / 2)
		return quickselect(from, medians_to, median_sorted_idx)
	end
end)
