
return function(
	n,
	shift
)
	local highest_bits = math.floor(n / 2 ^ (53 - shift))
	return (n * 2 ^ shift) % 2 ^ 53 + highest_bits
end
