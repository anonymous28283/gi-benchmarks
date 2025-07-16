
local bytes = {}
for byte = 0, 0xFF do
	local res = 0
	for i = 0, 7 do
		local bit = math.floor(byte / (2 ^ i)) % 2
		res = res + 2 ^ i * (1 - bit)
	end
	bytes[byte] = res
end

return function(
	n
)
	local res = 0
	local bit = 1

	while n >= 0xFF do
		local byte = n % 0x100
		res = res + bytes[byte] * bit
		n = (n - byte) / 0x100
		bit = bit * 0x100
	end

	while n ~= 0 do
		local n_bit = n % 2
		res = res + (1 - n_bit) * bit
		n = (n - n_bit) / 2
		bit = bit * 2
	end
	local leading_ones = 2 ^ 53 - bit
	return leading_ones + res
end
