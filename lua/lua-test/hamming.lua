

return function(
	a,
	b
)
	assert(#a == #b, "lengths don't match")
	local dist = 0
	for i = 1, #a do
		if a:byte(i) ~= b:byte(i) then
			dist = dist + 1
		end
	end
	return dist
end
