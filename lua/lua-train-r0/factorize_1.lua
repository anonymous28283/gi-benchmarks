
return function(
	n
)
	local factors = {}
	for factor = 2, n ^ 0.5 do
		local count = 0
		while n % factor == 0 do
			count = count + 1
			n = n / factor
		end
		if count > 0 then
			factors[factor] = count
		end
	end
	if next(factors) == nil then
		factors[n] = 1
	end

	return factors
end
