return function(
	radix
)
	radix = radix or 16
	return function(list)
		if #list == 0 then
			return
		end
		local div = 1
		while true do
			local by_digit = {}
			local max_place = true
			for i = 1, radix do
				by_digit[i] = {}
			end
			for _, number in ipairs(list) do
				local quotient = math.floor(number / div)
				max_place = max_place and (quotient == 0)
				table.insert(by_digit[(quotient % radix) + 1], number)
			end
			if max_place then
				return
			end
			local index = 1
			for _, numbers in ipairs(by_digit) do
				for _, number in ipairs(numbers) do
					list[index] = number
					index = index + 1
				end
			end
			div = div * radix
		end
	end
end
