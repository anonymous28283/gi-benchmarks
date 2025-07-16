


local table_heap = require("data_structures.table_heap")

local graph = {}

function graph.new(
	nodes
)
	return { _nodes = nodes or {} }
end

function graph:add_node(node)
	assert(self._nodes[node] == nil, "node already exists")
	self._nodes[node] = {}
end





function graph:has_node(node)
	return self._nodes[node] ~= nil
end



function graph:set_weight(
	from,
	to,
	weight
)
	assert(self._nodes[to], "destination node missing")
	assert(self._nodes[from], "source node missing")[to] = weight
end


function graph:get_weight(
	from,
	to
)
	return self._nodes[from] and self._nodes[from][to]
end


function graph:has_edge(
	from,
	to
)
	return self:get_weight(from, to) ~= nil
end


function graph:add_edge(
	from,
	to
)
	assert(self:get_weight(from, to) == nil, "edge already exists")
	return self:set_weight(from, to, true)
end


function graph:remove_edge(
	from,
	to
)
	return self:set_weight(from, to, nil)
end



function graph:copy()
	local nodes_copy = {}
	for node, neighbors in pairs(self._nodes) do
		local neighbors_copy = {}
		for neighbor, weight in pairs(neighbors) do
			neighbors_copy[neighbor] = weight
		end
		nodes_copy[node] = neighbors_copy
	end
	return graph.new(nodes_copy)
end

local function next_key(t, k)
	return (next(t, k))
end

function graph:nodes()

	return next_key, self._nodes
end

function graph:neighbors(
	from
)

	return pairs(self._nodes[from])
end

function graph:edges()

	return coroutine.wrap(function()
		for from, tos in pairs(self._nodes) do
			for to, weight in pairs(tos) do
				coroutine.yield(from, to, weight)
			end
		end
	end)
end


function graph:transposed()
	local transposed = graph.new()
	for node in self:nodes() do
		transposed:add_node(node)
	end
	for from, to, weight in self:edges() do
		transposed:set_weight(to, from, weight)
	end
	return transposed
end


function graph:nodes_breadth_first(
	root
)
	local visited = {}
	local function breadth_first_traversal(start)
		visited[start] = true
		local level = { start }
		local depth = 0
		coroutine.yield(start, depth, nil)
		repeat
			local next_level = {}
			depth = depth + 1
			for _, node in pairs(level) do
				for neighbor in self:neighbors(node) do
					if not visited[neighbor] then
						coroutine.yield(neighbor, depth, node)
						table.insert(next_level, neighbor)
						visited[neighbor] = true
					end
				end
			end
			level = next_level
		until level[1] == nil
	end

	return coroutine.wrap(function()
		if root ~= nil then
			assert(self._nodes[root])
			return breadth_first_traversal(root)
		end
		for start in self:nodes() do
			if not visited[start] then
				breadth_first_traversal(start)
			end
		end
	end)
end


function graph:nodes_depth_first(
	root
)
	local visited = {}
	local depth = 0
	local function depth_first_traversal(node)
		if visited[node] then
			return
		end
		visited[node] = true
		coroutine.yield(node, depth)
		depth = depth + 1
		for neighbor in self:neighbors(node) do
			depth_first_traversal(neighbor)
		end
		depth = depth - 1
	end

	return coroutine.wrap(function()
		if root ~= nil then
			assert(self._nodes[root])
			return depth_first_traversal(root)
		end
		for node in self:nodes() do
			depth_first_traversal(node)
		end
	end)
end


function graph:has_cycle()
	local done = {}
	local function has_cycle(node)
		if done[node] == false then
			return true
		end
		if done[node] == true then
			return false
		end
		done[node] = false
		for neighbor in self:neighbors(node) do
			if has_cycle(neighbor) then
				return true
			end
		end
		done[node] = true
		return false
	end
	for node in self:nodes() do
		if has_cycle(node) then
			return true
		end
	end
	return false
end




function graph:nodes_topological_order()

	local roots = {}
	for node in self:nodes() do
		roots[node] = true
	end
	for _, to in self:edges() do
		roots[to] = nil
	end
	local nodes = {}
	local done = {}
	local function topo_sort(node)
		if done[node] then
			return
		end

		assert(done[node] == nil, "graph contains cycle")
		done[node] = false
		for neighbor in self:neighbors(node) do
			topo_sort(neighbor)
		end
		done[node] = true
		table.insert(nodes, node)
	end

	for root in pairs(roots) do
		topo_sort(root)
	end

	for node in self:nodes() do
		assert(done[node], "graph contains cycle")
	end

	local i = #nodes + 1
	return function()
		i = i - 1
		return nodes[i]
	end
end



function graph:strongly_connected_components()
	local nodes_depth_first = {}
	do
		local seen = {}
		local function visit(node)
			if seen[node] then
				return
			end
			seen[node] = true
			for neighbor in self:neighbors(node) do
				visit(neighbor)
			end
			table.insert(nodes_depth_first, node)
		end
		for node in self:nodes() do
			visit(node)
		end
	end
	local transposed = self:transposed()
	local seen = {}
	local connected_components = {}
	for i = #nodes_depth_first, 1, -1 do
		local root = nodes_depth_first[i]
		if not seen[root] then
			seen[root] = true
			local component = {}
			local to_visit = { root }
			repeat
				local node = table.remove(to_visit)
				component[node] = true
				for neighbor in transposed:neighbors(node) do
					if not seen[neighbor] then
						seen[neighbor] = true
						table.insert(to_visit, neighbor)
					end
				end
			until to_visit[1] == nil
			table.insert(connected_components, component)
		end
	end
	return connected_components
end



function graph:sssp_dijkstra(source)
	local dist, predec = {}, {}
	dist[source] = 0
	local closest = table_heap.new({}, function(v, w)
		return dist[v] < dist[w]
	end)
	closest:push(source)
	repeat
		local closest_node = closest:pop()
		for neighbor, weight in self:neighbors(closest_node) do
			assert(weight >= 0, "negative weight edge")
			local candidate_dist = dist[closest_node] + weight
			if dist[neighbor] == nil then
				dist[neighbor], predec[neighbor] = candidate_dist, closest_node
				closest:push(neighbor)
			elseif candidate_dist < dist[neighbor] then
				dist[neighbor], predec[neighbor] = candidate_dist, closest_node
				closest:decrease(neighbor)
			end
		end
	until closest:top() == nil
	return dist, predec
end



function graph:sssp_bellman_ford(source)
	local dist, predec = {}, {}
	dist[source] = 0
	for _ in next, self._nodes, next(self._nodes) do
		for from, to, weight in self:edges() do
			if dist[from] then
				local candidate_dist = dist[from] + weight

				if dist[to] == nil or candidate_dist < dist[to] then

					dist[to], predec[to] = candidate_dist, from
				end
			end
		end
	end

	for from, to, weight in self:edges() do
		if dist[from] then
			local candidate_dist = dist[from] + weight
			if dist[to] == nil or candidate_dist < dist[to] then
				error("negative weight cycle")
			end
		end
	end
	return dist, predec
end






function graph:sssp(
	source
)
	for _, _, weight in self:edges() do
		if weight < 0 then
			return self:sssp_bellman_ford(source)
		end
	end
	return self:sssp_dijkstra(source)
end


local function _apsp_sssp(self, sssp_name)
	local dist, predec = {}, {}
	for node in self:nodes() do
		dist[node], predec[node] = self[sssp_name](self, node)
	end
	return dist, predec
end



function graph:apsp_dijkstra()
	return _apsp_sssp(self, "sssp_dijkstra")
end



function graph:apsp_bellman_ford()
	return _apsp_sssp(self, "sssp_bellman_ford")
end




function graph:apsp_floyd_warshall()
	local dist, predec = {}, {}
	for from in self:nodes() do
		dist[from], predec[from] = {}, {}
		for to, weight in self:neighbors(from) do
			dist[from][to], predec[from][to] = weight, from
		end
		dist[from][from] = 0
	end
	for over in self:nodes() do
		for from in self:nodes() do
			for to in self:nodes() do
				local d_fo, d_ot = dist[from][over], dist[over][to]
				if d_fo and d_ot then
					local d = dist[from][to]
					local d_over = d_fo + d_ot
					if d == nil or d_over < d then


						dist[from][to], predec[from][to] = d_over, predec[over][to]
					end
				end
			end
		end
	end
	for node in self:nodes() do
		assert(dist[node][node] == 0, "negative weight cycle")
	end
	return dist, predec
end







function graph:apsp()

	local nodes = 0
	for _ in self:nodes() do
		nodes = nodes + 1
	end
	local edges = 0
	local negative_weight = false
	for _, _, weight in self:edges() do
		edges = edges + 1
		if weight < 0 then
			negative_weight = true
		end
	end
	if negative_weight then
		if edges >= nodes then

			return self:apsp_floyd_warshall()
		end
		return self:apsp_bellman_ford()
	end

	local time_dijkstra = (nodes + edges) * math.log(nodes)
	local time_floyd_warshall = nodes ^ 2
	if time_floyd_warshall <= time_dijkstra then
		return self:apsp_floyd_warshall()
	end
	local time_bellman_ford = nodes * edges

	if time_bellman_ford <= time_dijkstra then
		return self:apsp_bellman_ford()
	end
	return self:apsp_dijkstra()
end


function graph:shortest_paths(
	source
)
	if source == nil then
		return self:apsp()
	end
	return self:sssp(source)
end






function graph:max_flow(source, sink)
	local residual = self:copy()

	local function calc_max_augment(predec)
		local max_augment = math.huge
		local to = sink
		repeat
			local from = predec[to]
			max_augment = math.min(max_augment, residual:get_weight(from, to))
			to = from
		until to == source
		return max_augment
	end

	local function augment_path(predec)
		local max_augment = calc_max_augment(predec)
		local to = sink
		repeat
			local from = predec[to]
			residual:set_weight(from, to, residual:get_weight(from, to) - max_augment)
			residual:set_weight(to, from, (residual:get_weight(to, from) or 0) + max_augment)
			to = from
		until to == source
	end



	local function try_augment_path()
		local level = { source }
		local predec = { [source] = source }
		repeat
			local next_level = {}
			for _, node in ipairs(level) do
				for neighbor, capacity in residual:neighbors(node) do
					if capacity > 0 and predec[neighbor] == nil then
						predec[neighbor] = node
						if neighbor == sink then
							augment_path(predec)
							return try_augment_path()
						end
						table.insert(next_level, neighbor)
					end
				end
			end
			level = next_level
		until #level == 0
	end
	try_augment_path()

	local flow = self:copy()
	for from, to in flow:edges() do

		flow:set_weight(from, to, residual:get_weight(to, from))
	end
	return flow
end

return require("class")(graph)
