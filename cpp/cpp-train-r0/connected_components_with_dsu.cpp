






namespace graph {

namespace disjoint_union {
uint32_t number_of_nodes = 0;
std::vector<int64_t> parent{};
std::vector<uint32_t> connected_set_size{};

void make_set() {
    for (uint32_t i = 1; i <= number_of_nodes; i++) {
        parent[i] = i;
        connected_set_size[i] = 1;
    }
}

int64_t find_set(int64_t val) {
    while (parent[val] != val) {
        parent[val] = parent[parent[val]];
        val = parent[val];
    }
    return val;
}

void union_sets(int64_t node1, int64_t node2) {
    node1 = find_set(node1);
    node2 = find_set(node2);


    if (node1 != node2) {
        if (connected_set_size[node1] < connected_set_size[node2]) {
            std::swap(node1, node2);
        }
        parent[node2] = node1;
        connected_set_size[node1] +=
            connected_set_size[node2];
    }
}

uint32_t no_of_connected_components() {
    std::set<int64_t> temp;
    for (uint32_t i = 1; i <= number_of_nodes; i++) temp.insert(find_set(i));
    return temp.size();
}
}
}


static void test() {
    namespace dsu = graph::disjoint_union;
    std::cin >> dsu::number_of_nodes;
    dsu::parent.resize(dsu::number_of_nodes + 1);
    dsu::connected_set_size.resize(dsu::number_of_nodes + 1);
    dsu::make_set();
    uint32_t edges = 0;
    std::cin >> edges;
    while (edges--) {
        int64_t node_a = 0, node_b = 0;
        std::cin >> node_a >> node_b;
        dsu::union_sets(node_a, node_b);
    }
    std::cout << dsu::no_of_connected_components() << std::endl;
}


int main() {
    test();
    return 0;
}
