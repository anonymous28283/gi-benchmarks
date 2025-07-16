








namespace graph {

class Graph {
 public:

    Graph(size_t N, const std::vector<std::pair<int, int> > &undirected_edges) {
        neighbors.resize(N);
        for (auto &edge : undirected_edges) {
            neighbors[edge.first].push_back(edge.second);
            neighbors[edge.second].push_back(edge.first);
        }
    }


    int number_of_vertices() const { return neighbors.size(); }


    std::vector<std::vector<int> > neighbors;
};


class RootedTree : public Graph {
 public:

    RootedTree(const std::vector<std::pair<int, int> > &undirected_edges,
               int root_)
        : Graph(undirected_edges.size() + 1, undirected_edges), root(root_) {
        populate_parents();
    }


    std::vector<int> parent;

    std::vector<int> level;

    int root;

 protected:

    void populate_parents() {


        parent = std::vector<int>(number_of_vertices(), -1);
        level = std::vector<int>(number_of_vertices());
        parent[root] = root;
        level[root] = 0;
        std::queue<int> queue_of_vertices;
        queue_of_vertices.push(root);
        while (!queue_of_vertices.empty()) {
            int vertex = queue_of_vertices.front();
            queue_of_vertices.pop();
            for (int neighbor : neighbors[vertex]) {

                if (parent[neighbor] == -1) {
                    parent[neighbor] = vertex;
                    level[neighbor] = level[vertex] + 1;
                    queue_of_vertices.push(neighbor);
                }
            }
        }
    }
};


class LowestCommonAncestor {
 public:

    explicit LowestCommonAncestor(const RootedTree &tree_) : tree(tree_) {
        populate_up();
    }


    int lowest_common_ancestor(int u, int v) const {

        if (tree.level[v] > tree.level[u]) {
            std::swap(u, v);
        }


        int level_diff = tree.level[u] - tree.level[v];
        for (int i = 0; (1 << i) <= level_diff; ++i) {
            if (level_diff & (1 << i)) {
                u = up[u][i];
            }
        }
        assert(tree.level[u] == tree.level[v]);

        if (u == v) {
            return u;
        }


        for (int i = static_cast<int>(up[u].size()) - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }




        assert(up[u][0] == up[v][0]);
        return up[u][0];
    }


    const RootedTree &tree;

    std::vector<std::vector<int> > up;

 protected:

    void populate_up() {
        up.resize(tree.number_of_vertices());
        for (int vertex = 0; vertex < tree.number_of_vertices(); ++vertex) {
            up[vertex].push_back(tree.parent[vertex]);
        }
        for (int level = 0; (1 << level) < tree.number_of_vertices(); ++level) {
            for (int vertex = 0; vertex < tree.number_of_vertices(); ++vertex) {



                up[vertex].push_back(up[up[vertex][level]][level]);
            }
        }
    }
};

}


static void tests() {

    std::vector<std::pair<int, int> > edges = {
        {7, 1}, {1, 5}, {1, 3}, {3, 6}, {6, 2}, {2, 9}, {6, 8}, {4, 3}, {0, 4}};
    graph::RootedTree t(edges, 3);
    graph::LowestCommonAncestor lca(t);
    assert(lca.lowest_common_ancestor(7, 4) == 3);
    assert(lca.lowest_common_ancestor(9, 6) == 6);
    assert(lca.lowest_common_ancestor(0, 0) == 0);
    assert(lca.lowest_common_ancestor(8, 2) == 6);
}


int main() {
    tests();
    return 0;
}
