local gcd = require("math.greatest_common_divisor")
return function(
	a,
	b
)

	return math.abs(a / gcd(a, b) * b)
end
