return function(

	list,

	less_than
)
	less_than = less_than or function(a, b)
		return a < b
	end
	local heap_size = #list
	local function max_heapify_down(index)
		local left_child = index * 2
		if left_child > heap_size then
			return
		end
		local largest_child = left_child + 1
		if largest_child > heap_size or less_than(list[largest_child], list[left_child]) then
			largest_child = left_child
		end
		if less_than(list[index], list[largest_child]) then
			list[index], list[largest_child] = list[largest_child], list[index]
			max_heapify_down(largest_child)
		end
	end

	for index = math.floor(#list / 2), 1, -1 do
		max_heapify_down(index)
	end
	while heap_size > 0 do

		list[1], list[heap_size] = list[heap_size], list[1]
		heap_size = heap_size - 1
		max_heapify_down(1)
	end
end
