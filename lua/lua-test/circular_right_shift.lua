
return function(
	n,
	shift
)
	local lowest = n % 2 ^ shift
	return lowest * 2 ^ (53 - shift) + math.floor(n / 2 ^ shift)
end
