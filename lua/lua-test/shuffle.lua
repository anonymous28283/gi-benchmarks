
return function(
	list
)
	for i = 1, #list - 1 do
		local j = math.random(i, #list)
		list[i], list[j] = list[j], list[i]
	end
end
