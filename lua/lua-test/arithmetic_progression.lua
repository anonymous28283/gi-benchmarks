
return function(
	from,
	to,
	step
)
	if from > to then
		assert(step < 0, "empty interval")
	end
	step = step or 1
	local count = math.floor((to - from) / step)
	local last = from + count * step

	return (count + 1) * (from + last) / 2
end
