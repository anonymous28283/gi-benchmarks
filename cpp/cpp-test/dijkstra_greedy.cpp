







namespace greedy_algorithms {

namespace dijkstra {

class Graph {
 public:
    int vertexNum = 0;
    std::vector<std::vector<int>> edges{};


    explicit Graph(const int V) {

        this->edges = std::vector<std::vector<int>>(V, std::vector<int>(V, 0));
        for (int i = 0; i < V; i++) {
            edges[i] = std::vector<int>(V, 0);
        }


        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                edges[i][j] = 0;
            }
        }

        this->vertexNum = V;
    }


    void add_edge(int src, int dst, int weight) {
        this->edges[src][dst] = weight;
    }
};


int minimum_distance(std::vector<int> mdist, std::vector<bool> vset, int V) {
    int minVal = INT_MAX, minInd = 0;
    for (int i = 0; i < V; i++) {
        if (!vset[i] && (mdist[i] < minVal)) {
            minVal = mdist[i];
            minInd = i;
        }
    }

    return minInd;
}


void print(std::vector<int> dist, int V) {
    std::cout << "\nVertex  Distance\n";
    for (int i = 0; i < V; i++) {
        if (dist[i] < INT_MAX) {
            std::cout << i << "\t" << dist[i] << "\n";
        }
        else {
            std::cout << i << "\tINF" << "\n";
        }
    }
}


void dijkstra(Graph graph, int src) {
    int V = graph.vertexNum;
    std::vector<int> mdist{};
    std::vector<bool> vset{};


    for (int i = 0; i < V; i++) {
        mdist[i] = INT_MAX;
        vset[i] = false;
    }

    mdist[src] = 0;


    for (int count = 0; count < V - 1; count++) {
        int u = minimum_distance(mdist, vset, V);

        vset[u] = true;

        for (int v = 0; v < V; v++) {
            if (!vset[v] && graph.edges[u][v] &&
                mdist[u] + graph.edges[u][v] < mdist[v]) {
                mdist[v] = mdist[u] + graph.edges[u][v];
            }
        }
    }

    print(mdist, V);
}
}
}


static void tests() {
    greedy_algorithms::dijkstra::Graph graph(8);


    graph.add_edge(6, 2, 4);
    graph.add_edge(2, 6, 4);

    assert(graph.edges[6][2] == 4);


    graph.add_edge(0, 1, 1);
    graph.add_edge(1, 0, 1);

    assert(graph.edges[0][1] == 1);


    graph.add_edge(0, 2, 7);
    graph.add_edge(2, 0, 7);
    graph.add_edge(1, 2, 1);
    graph.add_edge(2, 1, 1);

    assert(graph.edges[0][2] == 7);


    graph.add_edge(1, 3, 3);
    graph.add_edge(3, 1, 3);
    graph.add_edge(1, 4, 2);
    graph.add_edge(4, 1, 2);
    graph.add_edge(2, 3, 2);

    assert(graph.edges[1][3] == 3);

    std::cout << "All tests have successfully passed!\n";
}


int main() {
    tests();
    return 0;
}
