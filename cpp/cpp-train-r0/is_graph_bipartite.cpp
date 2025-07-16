





namespace graph {

namespace is_graph_bipartite {

class Graph {
 private:
    int n;

    std::vector<std::vector<int> >
        adj;

    std::vector<int> side;

 public:

    explicit Graph(int size) {
        n = size;
        adj.resize(n);
        side.resize(n, -1);
    }

    void addEdge(int u, int v);

    bool
    is_bipartite();
};


void Graph::addEdge(int u, int v) {
    adj[u - 1].push_back(v - 1);
    adj[v - 1].push_back(u - 1);
}


bool Graph::is_bipartite() {
    bool check = true;
    std::queue<int> q;
    for (int current_edge = 0; current_edge < n; ++current_edge) {
        if (side[current_edge] == -1) {
            q.push(current_edge);
            side[current_edge] = 0;
            while (q.size()) {
                int current = q.front();
                q.pop();
                for (auto neighbour : adj[current]) {
                    if (side[neighbour] == -1) {
                        side[neighbour] = (1 ^ side[current]);
                        q.push(neighbour);
                    } else {
                        check &= (side[neighbour] != side[current]);
                    }
                }
            }
        }
    }
    return check;
}
}
}


static void test() {
    graph::is_graph_bipartite::Graph G1(
        5);

    G1.addEdge(1, 2);
    G1.addEdge(1, 3);
    G1.addEdge(3, 4);
    G1.addEdge(4, 5);

    graph::is_graph_bipartite::Graph G2(
        3);

    G2.addEdge(1, 2);
    G2.addEdge(1, 3);
    G2.addEdge(2, 3);


    if (G1.is_bipartite()) {
        std::cout << "The given graph G1 is a bipartite graph\n";
    } else {
        std::cout << "The given graph G1 is not a bipartite graph\n";
    }
    if (G2.is_bipartite()) {
        std::cout << "The given graph G2 is a bipartite graph\n";
    } else {
        std::cout << "The given graph G2 is not a bipartite graph\n";
    }
}


int main() {
    test();
    return 0;
}
