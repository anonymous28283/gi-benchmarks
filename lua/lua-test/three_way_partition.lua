




return function(arr, from, to, pivot_val, less_than)
	local i = from
	local j = from
	local k = to
	while j <= k do
		if less_than(arr[j], pivot_val) then
			arr[i], arr[j] = arr[j], arr[i]
			i, j = i + 1, j + 1
		elseif less_than(pivot_val, arr[j]) then
			arr[j], arr[k] = arr[k], arr[j]
			k = k - 1
		else
			j = j + 1
		end
	end
	return i - 1, k + 1
end
