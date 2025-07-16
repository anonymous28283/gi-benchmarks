return function(
	n
)
	local fac = 1
	for m = 2, n do
		fac = fac * m
	end
	return fac
end