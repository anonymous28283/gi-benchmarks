local function inextbit(n, i)
	if n < 2 ^ i then
		return
	end
	local bit = math.floor((n % 2 ^ (i + 1)) / 2 ^ i)
	return i + 1, bit
end



return function(
	n
)

	return inextbit, n, 0
end
