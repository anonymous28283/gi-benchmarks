

return function(
	s,
	t
)



	local prev_row, cur_row = {}, {}


	for j = 0, #t do
		prev_row[j] = j
	end

	for i = 1, #s do

		cur_row[0] = i
		for j = 1, #t do
			cur_row[j] = s:byte(i) == t:byte(j) and prev_row[j - 1]
				or 1
					+ math.min(
						prev_row[j - 1],
						prev_row[j],
						cur_row[j - 1]
					)
		end
		prev_row, cur_row = cur_row, prev_row
	end

	return prev_row[#t]
end
