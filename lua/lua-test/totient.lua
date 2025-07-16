local gcd = require("math.greatest_common_divisor")

return function(
	n
)
	local totient = 0
	for i = 1, n do
		if gcd(i, n) == 1 then
			totient = totient + 1
		end
	end
	return totient
end
