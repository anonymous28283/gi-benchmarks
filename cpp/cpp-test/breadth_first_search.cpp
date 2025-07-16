










namespace graph {

template <typename T>
class Graph {

    std::map<T, std::list<T> > adjacency_list;

 public:
    Graph() = default;
    ;
    void add_edge(T u, T v, bool bidir = true) {

        adjacency_list[u].push_back(v);
        if (bidir == true) {

            adjacency_list[v].push_back(u);
        }
    }


    std::map<T, bool> breadth_first_search(T src) {

        std::map<T, bool> visited;


        for (auto const &adjlist : adjacency_list) {
            visited[adjlist.first] = false;
            for (auto const &node : adjacency_list[adjlist.first]) {
                visited[node] = false;
            }
        }


        std::queue<T> tracker;


        tracker.push(src);

        visited[src] = true;
        while (!tracker.empty()) {


            T node = tracker.front();

            tracker.pop();
            for (T const &neighbour : adjacency_list[node]) {


                if (!visited[neighbour]) {

                    tracker.push(neighbour);

                    visited[neighbour] = true;
                }
            }
        }
        return visited;
    }
};

}


static void tests() {

    graph::Graph<int> g;
    std::map<int, bool> correct_result;
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    correct_result[0] = true;
    correct_result[1] = true;
    correct_result[2] = true;
    correct_result[3] = true;

    std::map<int, bool> returned_result = g.breadth_first_search(2);

    assert(returned_result == correct_result);
    std::cout << "Test 1 Passed..." << std::endl;


    returned_result = g.breadth_first_search(0);

    assert(returned_result == correct_result);
    std::cout << "Test 2 Passed..." << std::endl;


    graph::Graph<std::string> g2;

    g2.add_edge("Gorakhpur", "Lucknow", false);
    g2.add_edge("Gorakhpur", "Kanpur", false);
    g2.add_edge("Lucknow", "Agra", false);
    g2.add_edge("Kanpur", "Agra", false);
    g2.add_edge("Lucknow", "Prayagraj", false);
    g2.add_edge("Agra", "Noida", false);

    std::map<std::string, bool> correct_res;
    std::map<std::string, bool> returned_res =
        g2.breadth_first_search("Kanpur");
    correct_res["Gorakhpur"] = false;
    correct_res["Lucknow"] = false;
    correct_res["Kanpur"] = true;
    correct_res["Agra"] = true;
    correct_res["Prayagraj"] = false;
    correct_res["Noida"] = true;
    assert(correct_res == returned_res);
    std::cout << "Test 3 Passed..." << std::endl;
}


int main() {
    tests();
    size_t edges = 0;
    std::cout << "Enter the number of edges: ";
    std::cin >> edges;

    graph::Graph<int> g;

    std::cout << "Enter space-separated pairs of vertices that form edges: "
              << std::endl;
    while (edges--) {
        int u = 0, v = 0;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    g.breadth_first_search(0);
    return 0;
}
