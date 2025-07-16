local function downscale(max, new_max, random)


	local max_i = max - max % new_max
	return function()



		local i
		repeat
			i = random()
		until i < max_i
		return i % new_max
	end
end

local function upscale(max, new_max, random)

	local function upscaled_random()
		local res, pow = 0, 1
		repeat
			res = res + pow * random()
			pow = pow * max
		until pow >= new_max
		return res
	end

	local pow = 1
	repeat
		pow = pow * max
	until pow >= new_max
	if pow == new_max then
		return upscaled_random
	end

	return downscale(pow, new_max, upscaled_random)
end



return function(
	max,
	new_max,
	random
)
	if new_max == max then
		return random
	end
	if new_max < max then
		return downscale(max, new_max, random)
	end
	return upscale(max, new_max, random)
end
