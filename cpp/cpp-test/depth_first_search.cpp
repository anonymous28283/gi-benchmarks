






namespace graph {

void addEdge(std::vector<std::vector<size_t>> *adj, size_t u, size_t v) {

    (*adj)[u - 1].push_back(v - 1);
    (*adj)[v - 1].push_back(u - 1);
}


void explore(const std::vector<std::vector<size_t>> &adj, size_t v,
             std::vector<bool> *visited) {
    std::cout << v + 1 << " ";
    (*visited)[v] = true;
    for (auto x : adj[v]) {
        if (!(*visited)[x]) {
            explore(adj, x, visited);
        }
    }
}


void depth_first_search(const std::vector<std::vector<size_t>> &adj,
                        size_t start) {
    size_t vertices = adj.size();

    std::vector<bool> visited(vertices, false);
    explore(adj, start, &visited);
}
}


int main() {
    size_t vertices = 0, edges = 0;
    std::cout << "Enter the Vertices : ";
    std::cin >> vertices;
    std::cout << "Enter the Edges : ";
    std::cin >> edges;


    std::vector<std::vector<size_t>> adj(vertices, std::vector<size_t>());


    std::cout << "Enter the vertices which have edges between them : "
              << std::endl;
    while (edges--) {
        size_t u = 0, v = 0;
        std::cin >> u >> v;
        graph::addEdge(&adj, u, v);
    }


    graph::depth_first_search(adj, 2);

    std::cout << std::endl;
    return 0;
}
