


return function(n)
	assert(n > 0, "input must be positive")
	if n == 1 then
		return 0
	end
	local res = 1
	for i = 2, math.sqrt(n) do
		if n % i == 0 then
			res = res + i
			local complement = n / i

			if complement ~= i then
				res = res + complement
			end
		end
	end
	return res
end
