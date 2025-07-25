return function(

	list,

	key_function
)
	if list[1] == nil then
		return
	end

	key_function = key_function or function(x)
		return x
	end


	local min_key, max_key = math.huge, -math.huge
	for _, elem in ipairs(list) do
		local key = key_function(elem)
		min_key = math.min(min_key, key)
		max_key = math.max(max_key, key)
	end

	local count = {}
	for i = 1, max_key - min_key + 1 do
		count[i] = 0
	end


	for _, elem in ipairs(list) do
		local key = key_function(elem)
		count[key - min_key + 1] = count[key - min_key + 1] + 1
	end


	for i = 2, #count do
		count[i] = count[i] + count[i - 1]
	end

	local output = {}
	for i = #list, 1, -1 do
		local element = list[i]
		local key = key_function(element)
		output[count[key - min_key + 1]] = element
		count[key - min_key + 1] = count[key - min_key + 1] - 1
	end

	for i, elem in ipairs(output) do
		list[i] = elem
	end
end
