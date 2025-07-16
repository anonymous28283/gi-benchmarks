
return function(
	n
)
	if n == 1 then
		return false
	end
	if n % 2 == 0 then
		return n == 2
	end
	for factor = 3, n ^ 0.5, 2 do
		if n % factor == 0 then
			return false
		end
	end
	return true
end
