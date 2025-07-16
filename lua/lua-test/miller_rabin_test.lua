local modpow = require("math.modpow")



return function(
	n,
	rounds
)

	if n == 1 then
		return false
	end
	if n % 2 == 0 then
		return n == 2
	end
	if n == 3 then
		return true
	end

	rounds = rounds or 100


	local d = n - 1
	local r = 0
	while d % 2 == 0 do
		r = r + 1
		d = d / 2
	end

	for _ = 1, rounds do
		local a = math.random(2, n - 2)
		local x = modpow(a, d, n)
		if x ~= 1 and x ~= n - 1 then
			local composite = true
			for _ = 1, rounds - 1 do
				x = x ^ 2 % n
				if x == n - 1 then
					composite = false
					break
				end
			end
			if composite then
				return false
			end
		end
	end

	return true
end
