








namespace graph {

void addEdge(std::vector<std::vector<int>> *adj, int u, int v) {
    (*adj)[u - 1].push_back(v - 1);
    (*adj)[v - 1].push_back(u - 1);
}


void explore(const std::vector<std::vector<int>> *adj, int u,
             std::vector<bool> *visited) {
    (*visited)[u] = true;
    for (auto v : (*adj)[u]) {
        if (!(*visited)[v]) {
            explore(adj, v, visited);
        }
    }
}


int getConnectedComponents(const std::vector<std::vector<int>> *adj) {
    int n = adj->size();
    int connected_components = 0;
    std::vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            explore(adj, i, &visited);
            connected_components++;
        }
    }
    return connected_components;
}
}


void tests() {
    std::cout << "Running predefined tests..." << std::endl;
    std::cout << "Initiating Test 1..." << std::endl;
    std::vector<std::vector<int>> adj1(9, std::vector<int>());
    graph::addEdge(&adj1, 1, 2);
    graph::addEdge(&adj1, 1, 3);
    graph::addEdge(&adj1, 3, 4);
    graph::addEdge(&adj1, 5, 7);
    graph::addEdge(&adj1, 5, 6);
    graph::addEdge(&adj1, 8, 9);

    assert(graph::getConnectedComponents(&adj1) == 3);
    std::cout << "Test 1 Passed..." << std::endl;

    std::cout << "Innitiating Test 2..." << std::endl;
    std::vector<std::vector<int>> adj2(10, std::vector<int>());
    graph::addEdge(&adj2, 1, 2);
    graph::addEdge(&adj2, 1, 3);
    graph::addEdge(&adj2, 1, 4);
    graph::addEdge(&adj2, 2, 3);
    graph::addEdge(&adj2, 3, 4);
    graph::addEdge(&adj2, 4, 8);
    graph::addEdge(&adj2, 4, 10);
    graph::addEdge(&adj2, 8, 10);
    graph::addEdge(&adj2, 8, 9);
    graph::addEdge(&adj2, 5, 7);
    graph::addEdge(&adj2, 5, 6);
    graph::addEdge(&adj2, 6, 7);

    assert(graph::getConnectedComponents(&adj2) == 2);
    std::cout << "Test 2 Passed..." << std::endl;
}


int main() {

    tests();

    int vertices = int(), edges = int();
    std::cout << "Enter the number of vertices : ";
    std::cin >> vertices;
    std::cout << "Enter the number of edges : ";
    std::cin >> edges;

    std::vector<std::vector<int>> adj(vertices, std::vector<int>());

    int u = int(), v = int();
    while (edges--) {
        std::cin >> u >> v;
        graph::addEdge(&adj, u, v);
    }

    int cc = graph::getConnectedComponents(&adj);
    std::cout << cc << std::endl;
    return 0;
}
