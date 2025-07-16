return function(
	n,
	from,
	to
)
	from, to = from or 1, to or 53
	return math.floor((n % 2 ^ to) / 2 ^ (from - 1))
end
