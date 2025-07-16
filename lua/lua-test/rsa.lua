local test_prime = require("math.prime.miller_rabin_test")
local find_gcd = require("math.greatest_common_divisor")
local modpow = require("math.modpow")

local rsa = {}


function rsa.generate_key_pair(
	gen_rand_num
)
	local function random_prime()
		local prime
		repeat
			prime = gen_rand_num()
		until test_prime(prime)
		return prime
	end
	local p, q = random_prime(), random_prime()
	local n = p * q
	local phi_n = (p - 1) * (q - 1)

	local e, gcd, _, d
	repeat
		e = gen_rand_num()
		gcd, _, d = find_gcd(phi_n, e)
	until gcd == 1
	d = d % phi_n
	return n,
		e,
		d
end


function rsa.cryption(
	n,
	e_or_d,
	m
)
	return modpow(m, e_or_d, n)
end

return rsa
