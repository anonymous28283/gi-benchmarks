return function(
	any
)

	return type(any) == "number" and any % 1 == 0 and any >= 0 and any < 2 ^ 53
end
