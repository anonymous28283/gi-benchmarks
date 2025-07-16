
return function(
	n,
	m
)
	local res = 0
	local bit = 1
	while n * m ~= 0 do
		local n_bit, m_bit = n % 2, m % 2
		res = res + (n_bit * m_bit) * bit
		n, m = (n - n_bit) / 2, (m - m_bit) / 2
		bit = bit * 2
	end
	return res
end
