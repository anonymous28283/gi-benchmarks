
return function(
	intervals
)
	local selected_intervals = {}

	table.sort(intervals, function(a, b)
		return a.to < b.to
	end)

	table.insert(selected_intervals, intervals[1])
	for _, interval in ipairs(intervals) do
		if interval.from >= selected_intervals[#selected_intervals].to then
			table.insert(selected_intervals, interval)
		end
	end

	return selected_intervals
end
