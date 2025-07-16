
return function(
	n,
	shift
)
	return (n * 2 ^ shift) % 2 ^ 53
end
