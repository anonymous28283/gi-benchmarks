









namespace graph {


namespace topological_sort {

class Graph {
 private:
    int n;
    std::vector<std::vector<int>> adj;

 public:

    Graph(int nodes) : n(nodes), adj(nodes) {}


    void addEdge(int u, int v) { adj[u].push_back(v); }


    const std::vector<std::vector<int>>& getAdjacencyList() const {
        return adj;
    }


    int getNumNodes() const { return n; }
};


void dfs(int v, std::vector<int>& visited,
         const std::vector<std::vector<int>>& graph, std::stack<int>& s) {
    visited[v] = 1;
    for (int neighbour : graph[v]) {
        if (!visited[neighbour]) {
            dfs(neighbour, visited, graph, s);
        }
    }
    s.push(v);
}


std::vector<int> topologicalSort(const Graph& g) {
    int n = g.getNumNodes();
    const auto& adj = g.getAdjacencyList();
    std::vector<int> visited(n, 0);
    std::stack<int> s;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, visited, adj, s);
        }
    }

    std::vector<int> ans;
    while (!s.empty()) {
        int elem = s.top();
        s.pop();
        ans.push_back(elem);
    }

    if (ans.size() < n) {
        throw std::invalid_argument("cycle detected in graph");
    }
    return ans;
}
}
}


static void test() {

    std::cout << "Testing for graph 1\n";
    int n_1 = 6;
    graph::topological_sort::Graph graph1(n_1);
    graph1.addEdge(4, 0);
    graph1.addEdge(5, 0);
    graph1.addEdge(5, 2);
    graph1.addEdge(2, 3);
    graph1.addEdge(3, 1);
    graph1.addEdge(4, 1);
    std::vector<int> ans_1 = graph::topological_sort::topologicalSort(graph1);
    std::vector<int> expected_1 = {5, 4, 2, 3, 1, 0};
    std::cout << "Topological Sorting Order: ";
    for (int i : ans_1) {
        std::cout << i << " ";
    }
    std::cout << '\n';
    assert(ans_1 == expected_1);
    std::cout << "Test Passed\n\n";


    std::cout << "Testing for graph 2\n";
    int n_2 = 5;
    graph::topological_sort::Graph graph2(n_2);
    graph2.addEdge(0, 1);
    graph2.addEdge(0, 2);
    graph2.addEdge(1, 2);
    graph2.addEdge(2, 3);
    graph2.addEdge(1, 3);
    graph2.addEdge(2, 4);
    std::vector<int> ans_2 = graph::topological_sort::topologicalSort(graph2);
    std::vector<int> expected_2 = {0, 1, 2, 4, 3};
    std::cout << "Topological Sorting Order: ";
    for (int i : ans_2) {
        std::cout << i << " ";
    }
    std::cout << '\n';
    assert(ans_2 == expected_2);
    std::cout << "Test Passed\n\n";


    std::cout << "Testing for graph 3\n";
    int n_3 = 3;
    graph::topological_sort::Graph graph3(n_3);
    graph3.addEdge(0, 1);
    graph3.addEdge(1, 2);
    graph3.addEdge(2, 0);
    try {
        graph::topological_sort::topologicalSort(graph3);
    } catch (std::invalid_argument& err) {
        assert(std::string(err.what()) == "cycle detected in graph");
    }
    std::cout << "Test Passed\n";
}


int main() {
    test();
    return 0;
}
