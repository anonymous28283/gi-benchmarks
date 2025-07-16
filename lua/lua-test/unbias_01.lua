

return function(
	biased_01_random
)
	return function()
		local x, y
		repeat
			x, y = biased_01_random(), biased_01_random()
		until x ~= y
		return x
	end
end
