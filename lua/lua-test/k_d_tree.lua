


local k_d_tree = {}
local metatable = { __index = k_d_tree }

local function constructor(build_root)
	return function(points)
		if #points == 0 then
			return setmetatable({}, metatable)
		end
		local dimension = #points[1]
		for i = 2, #points do
			assert(#points[i] == dimension)
		end
		return setmetatable({ _root = build_root(points, dimension) }, metatable)
	end
end





k_d_tree.new_presorting = constructor(function(points, dimension)

	local value = {}
	for i = 1, #points do
		value[i] = 0
	end

	local presorted = {}
	for axis = 1, dimension do
		local idx = {}
		for i = 1, #points do
			idx[i] = i
		end
		table.sort(idx, function(i, j)
			return points[i][axis] < points[j][axis]
		end)
		presorted[axis] = idx
	end
	local function build(from, to, axis)
		if to < from then
			return
		end
		local mid = math.floor((from + to) / 2)
		local pidx_by_axis = presorted[axis]
		local midx = pidx_by_axis[mid]
		value[midx] = 0
		for i = from, mid - 1 do
			value[pidx_by_axis[i]] = -1
		end
		for i = mid + 1, to do
			value[pidx_by_axis[i]] = 1
		end
		local function partition_axis(a)
			local pidx_by_a = presorted[a]




			local right = {}
			local i = from
			for j = from, to do
				local pidx = pidx_by_a[j]
				if value[pidx] == -1 then

					pidx_by_a[i] = pidx
					i = i + 1
				elseif value[pidx] == 1 then

					table.insert(right, pidx)
				end
			end
			pidx_by_a[i] = midx
			for j = 1, #right do
				i = i + 1
				pidx_by_a[i] = right[j]
			end
		end
		for a = 1, axis - 1 do
			partition_axis(a)
		end
		for a = axis + 1, dimension do
			partition_axis(a)
		end
		local next_axis = axis + 1
		if next_axis > dimension then
			next_axis = 1
		end
		return {
			[true] = build(from, mid - 1, next_axis),
			[false] = build(mid + 1, to, next_axis),
			pivot = points[midx],
		}
	end
	return build(1, #points, 1)
end)


local function partition(sorted)
	local mid = math.ceil(#sorted / 2)
	local leq, geq = {}, {}
	for i = 1, mid - 1 do
		leq[i] = sorted[i]
	end
	for i = mid + 1, #sorted do
		table.insert(geq, sorted[i])
	end
	return leq, sorted[mid], geq
end





k_d_tree.new_sorting = constructor(function(points, dimension)
	local function build(points, axis)
		if #points == 0 then
			return
		end
		table.sort(points, function(p, q)
			return p[axis] < q[axis]
		end)


		local leq, pivot, geq = partition(points)
		local next_axis = axis + 1
		if next_axis > dimension then
			next_axis = 1
		end
		return {
			[true] = build(leq, next_axis),
			[false] = build(geq, next_axis),
			pivot = pivot,
		}
	end
	return build(points, 1)
end)

local quickselect = require("sorting.quickselect_median_of_medians")







k_d_tree.new_median_of_medians = constructor(function(points, dimension)
	local function build(from, to, axis)
		if to < from then
			return
		end
		local index = math.ceil((to - from + 1) / 2)




		local mid = quickselect(points, index, function(p, q)
			return p[axis] < q[axis]
		end, from, to)
		local next_axis = axis + 1
		if next_axis > dimension then
			next_axis = 1
		end
		return {
			[true] = build(from, mid - 1, next_axis),
			[false] = build(mid + 1, to, next_axis),
			pivot = points[mid],
		}
	end
	return build(1, #points, 1)
end)



k_d_tree.new = k_d_tree.new_median_of_medians

function k_d_tree:empty()
	return self._root == nil
end

function k_d_tree:nearest_neighbor(
	point
)
	if self:empty() then
		return
	end
	local root = self._root
	assert(#point == #root.pivot, "dimensions don't match")
	local min_dist, closest_point = math.huge, nil
	local function search_nearest_neighbor(node, axis)
		if not node then
			return
		end
		local pivot = node.pivot
		local dist = pivot:distance(point)
		if dist < min_dist then
			min_dist, closest_point = dist, pivot
		end
		local leq = point[axis] <= pivot[axis]
		local next_axis = axis + 1
		if next_axis > #point then
			next_axis = 1
		end
		search_nearest_neighbor(node[leq], next_axis)
		local dist_to_plane = math.abs(pivot[axis] - point[axis])
		if min_dist >= dist_to_plane then

			search_nearest_neighbor(node[not leq], next_axis)
		end
	end
	search_nearest_neighbor(root, 1)
	return min_dist, closest_point
end




function k_d_tree:insert(
	point
)
	if self:empty() then
		self._root = { pivot = point }
		return
	end
	local node = self._root
	assert(#point == #node.pivot, "dimensions don't match")
	local axis = 1
	while true do
		local pivot = node.pivot
		local left
		if point[axis] < pivot[axis] then
			left = true
		elseif point[axis] > pivot[axis] then
			left = false
		else


			left = math.random() < 0.5
		end

		if not node[left] then
			node[left] = { pivot = point }
			return
		end
		node = node[left]
		axis = axis + 1
		if axis > #point then
			axis = 1
		end
	end
end

return require("class")(k_d_tree)
