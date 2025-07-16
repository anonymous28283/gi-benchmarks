









namespace graph {

int TravellingSalesmanProblem(std::vector<std::vector<uint32_t>> *cities,
                              int32_t src, uint32_t V) {

    std::vector<uint32_t> vtx;
    for (uint32_t i = 0; i < V; i++) {
        if (i != src) {
            vtx.push_back(i);
        }
    }


    int32_t min_path = 2147483647;
    do {

        int32_t curr_weight = 0;


        int k = src;
        for (int i : vtx) {
            curr_weight += (*cities)[k][i];
            k = i;
        }
        curr_weight += (*cities)[k][src];


        min_path = std::min(min_path, curr_weight);

    } while (next_permutation(vtx.begin(), vtx.end()));

    return min_path;
}
}


static void tests() {
    std::cout << "Initiatinig Predefined Tests..." << std::endl;
    std::cout << "Initiating Test 1..." << std::endl;
    std::vector<std::vector<uint32_t>> cities = {
        {0, 20, 42, 35}, {20, 0, 30, 34}, {42, 30, 0, 12}, {35, 34, 12, 0}};
    uint32_t V = cities.size();
    assert(graph::TravellingSalesmanProblem(&cities, 0, V) == 97);
    std::cout << "1st test passed..." << std::endl;

    std::cout << "Initiating Test 2..." << std::endl;
    cities = {{0, 5, 10, 15}, {5, 0, 20, 30}, {10, 20, 0, 35}, {15, 30, 35, 0}};
    V = cities.size();
    assert(graph::TravellingSalesmanProblem(&cities, 0, V) == 75);
    std::cout << "2nd test passed..." << std::endl;

    std::cout << "Initiating Test 3..." << std::endl;
    cities = {
        {0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
    V = cities.size();
    assert(graph::TravellingSalesmanProblem(&cities, 0, V) == 80);
    std::cout << "3rd test passed..." << std::endl;
}


int main() {
    tests();
    std::vector<std::vector<uint32_t>> cities = {
        {0, 5, 10, 15}, {5, 0, 20, 30}, {10, 20, 0, 35}, {15, 30, 35, 0}};
    uint32_t V = cities.size();
    std::cout << graph::TravellingSalesmanProblem(&cities, 0, V) << std::endl;
    return 0;
}
