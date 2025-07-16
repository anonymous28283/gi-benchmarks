




local heap = require("data_structures.heap")
local table_heap = require("data_structures.table_heap")
local union_find = require("data_structures.union_find")
local graph = require("data_structures.graph")

local undirected_graph = {}





function undirected_graph.new(nodes)
	nodes = nodes or {}
	for from, tos in pairs(nodes) do
		for to, weight in pairs(tos) do
			assert(nodes[to], "destination node missing")
			if nodes[to][from] == nil then
				nodes[to][from] = weight
			else
				assert(nodes[to][from] == weight, "weights don't match")
			end
		end
	end
	return graph.new(nodes)
end



function undirected_graph:set_weight(
	node,
	other_node,
	weight
)
	graph.set_weight(self, node, other_node, weight)
	graph.set_weight(self, other_node, node, weight)
end



function undirected_graph:connected_components()
	local seen = {}
	local iterator, state, root = self:nodes()
	return function()
		repeat
			root = iterator(state, root)
		until not seen[root]
		if root == nil then
			return nil
		end
		local connected_component = undirected_graph.new()
		connected_component:add_node(root)
		local to_visit = { root }
		seen[root] = true
		repeat
			local node = table.remove(to_visit)
			for neighbor, weight in self:neighbors(node) do
				if not connected_component:has_node(neighbor) then
					connected_component:add_node(neighbor)
				end
				connected_component:set_weight(node, neighbor, weight)
				if not seen[neighbor] then
					seen[neighbor] = true
					table.insert(to_visit, neighbor)
				end
			end
		until #to_visit == 0
		return connected_component
	end
end


function undirected_graph:msf_prim()
	local spanning_forest = undirected_graph.new()

	local function grow_spanning_tree(root)
		local min_dist = {}
		local predec = {}

		local neighbors = table_heap.new({}, function(a, b)
			return min_dist[a] < min_dist[b]
		end)

		local function update_neighbors(node)
			for neighbor, weight in self:neighbors(node) do
				if not spanning_forest:has_node(neighbor) then
					if min_dist[neighbor] == nil then
						min_dist[neighbor], predec[neighbor] = weight, node
						neighbors:push(neighbor)
					elseif weight < min_dist[neighbor] then
						min_dist[neighbor], predec[neighbor] = weight, node
						neighbors:decrease(neighbor)
					end
				end
			end

			min_dist[node], predec[node] = nil, nil
		end

		spanning_forest:add_node(root)
		update_neighbors(root)
		while #neighbors > 0 do

			local node = neighbors:pop()
			spanning_forest:add_node(node)
			spanning_forest:set_weight(predec[node], node, min_dist[node])
			update_neighbors(node)
		end
	end


	local n_conn_comps = 0
	for root in self:nodes() do
		if not spanning_forest:has_node(root) then
			n_conn_comps = n_conn_comps + 1
			grow_spanning_tree(root)
		end
	end

	return spanning_forest, n_conn_comps
end


function undirected_graph:msf_kruskal()
	local spanning_forest = undirected_graph.new()


	local edges = {}
	for node, other_node, weight in self:edges() do
		table.insert(edges, { node = node, other_node = other_node, weight = weight })
	end
	edges = heap.new(edges, function(a, b)
		return a.weight < b.weight
	end)

	local connected_components = union_find.new()
	local n_conn_comps = 0
	for node in self:nodes() do
		spanning_forest:add_node(node)
		connected_components:make_set(node)
		n_conn_comps = n_conn_comps + 1
	end

	while n_conn_comps > 1 and not edges:empty() do
		local min_edge = edges:pop()
		local node, other_node = min_edge.node, min_edge.other_node


		if connected_components:find(node) ~= connected_components:find(other_node) then

			connected_components:union(node, other_node)
			spanning_forest:set_weight(node, other_node, min_edge.weight)
			n_conn_comps = n_conn_comps - 1
		end
	end

	return spanning_forest, n_conn_comps
end





undirected_graph.msf = undirected_graph.msf_prim

return require("class")(undirected_graph, graph)
