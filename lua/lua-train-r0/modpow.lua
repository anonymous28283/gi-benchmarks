

return function(
	base,
	exp,
	mod
)
	if exp == 0 then
		assert(base ~= 0)
		return 1 % mod
	end
	if base == 0 then
		return 0
	end
	local res = 1 % mod
	while exp > 0 do
		if exp % 2 == 1 then

			res = (res * base) % mod
			exp = exp - 1
		else

			base = (base * base) % mod
			exp = exp / 2
		end
	end
	return res
end
