







namespace graph {

bool checkBipartite(const std::vector<std::vector<int64_t>> &graph,
                    int64_t index, std::vector<int64_t> *visited) {
    std::queue<int64_t> q;

    q.push(index);
    (*visited)[index] = 1;
    while (q.size()) {
        int64_t u = q.front();
        q.pop();
        for (uint64_t i = 0; i < graph[u].size(); i++) {
            int64_t v =
                graph[u][i];
            if (!(*visited)[v])

            {
                (*visited)[v] =
                    ((*visited)[u] == 1)
                        ? -1
                        : 1;

                q.push(v);
            } else if ((*visited)[v] ==
                       (*visited)[u])


            {
                return false;
            }
        }
    }
    return true;

}

bool isBipartite(const std::vector<std::vector<int64_t>> &graph) {
    std::vector<int64_t> visited(
        graph.size());



    for (uint64_t i = 0; i < graph.size(); i++) {
        if (!visited[i])


        {
            if (!checkBipartite(graph, i, &visited)) {
                return false;
            }
        }
    }
    return true;
}
}


static void test() {
    std::vector<std::vector<int64_t>> graph = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};

    assert(graph::isBipartite(graph) ==
           true);


    std::vector<std::vector<int64_t>> graph_not_bipartite = {
        {1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2}};

    assert(graph::isBipartite(graph_not_bipartite) ==
           false);

    std::cout << "All tests have successfully passed!\n";
}

int main() {
    test();
    return 0;
}
