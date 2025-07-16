
return function(
	x
)
	if x == 0 then
		return 1, 0
	end
	assert(x > 0)
	local coefficient = 1
	local root_term = 1
	for factor = 2, math.sqrt(x) do
		local count = 0
		while x % factor == 0 do
			x = x / factor
			count = count + 1
		end
		coefficient = coefficient * factor ^ math.floor(count / 2)
		root_term = root_term * factor ^ (count % 2)
	end

	root_term = root_term * x

	return coefficient, root_term
end
