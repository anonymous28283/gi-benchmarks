




using PII = std::pair<int, int>;

int prim(int x, const std::vector<std::vector<PII> > &graph) {

    std::priority_queue<PII, std::vector<PII>, std::greater<PII> > Q;
    std::vector<bool> marked(graph.size(), false);
    int minimum_cost = 0;

    Q.push(std::make_pair(0, x));
    while (!Q.empty()) {

        PII p = Q.top();
        Q.pop();
        x = p.second;

        if (marked[x] == true) {
            continue;
        }
        minimum_cost += p.first;
        marked[x] = true;
        for (const PII &neighbor : graph[x]) {
            int y = neighbor.second;
            if (marked[y] == false) {
                Q.push(neighbor);
            }
        }
    }
    return minimum_cost;
}

int main() {
    int nodes = 0, edges = 0;
    std::cin >> nodes >> edges;
    if (nodes == 0 || edges == 0) {
        return 0;
    }

    std::vector<std::vector<PII> > graph(nodes);


    for (int i = 0; i < edges; ++i) {
        int x = 0, y = 0, weight = 0;
        std::cin >> x >> y >> weight;
        graph[x].push_back(std::make_pair(weight, y));
        graph[y].push_back(std::make_pair(weight, x));
    }


    int minimum_cost = prim(1, graph);
    std::cout << minimum_cost << std::endl;
    return 0;
}
