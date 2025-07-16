
return function(
	n,
	shift
)
	local msb = math.floor(n / 2 ^ 52)
	local vacant_bits = 2 ^ 53 - 1 - (2 ^ (53 - shift) - 1)
	return msb * vacant_bits + math.floor(n / 2 ^ shift)
end
