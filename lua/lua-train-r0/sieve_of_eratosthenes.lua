
return function(
	n
)
	assert(n > 0, "n must be positive")
	local is_prime = { false }
	for m = 2, n do
		is_prime[m] = true
	end
	for m = 2, math.sqrt(n) do
		if is_prime[m] then
			for l = m * m, n, m do
				is_prime[l] = false
			end
		end
	end
	return is_prime
end
