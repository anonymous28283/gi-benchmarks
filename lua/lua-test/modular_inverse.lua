local extended_gcd = require("math.greatest_common_divisor")




return function(
	a,
	m
)
	assert(m > 0, "modulus must be positive")
	if m == 1 then
		return nil
	end
	local gcd, x, _ = extended_gcd(a % m, m)
	if gcd == 1 then

		return x % m
	end
	return nil
end
