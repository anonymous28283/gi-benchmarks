
local byte_ones = {}
for byte = 0, 0xFF do
	local ones = 0

	local i = byte
	while i > 0 do
		local bit = i % 2
		ones = ones + bit
		i = (i - bit) / 2
	end
	byte_ones[byte] = ones
end


return function(
	n
)
	local ones = 0
	while n ~= 0 do
		local byte = n % 0x100
		ones = ones + byte_ones[byte]
		n = (n - byte) / 0x100
	end
	return ones
end
