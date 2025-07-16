







namespace greedy_algorithms {

template <typename T, std::size_t N, std::size_t M>
void findMinimumEdge(const T &infinity,
                     const std::array<std::array<T, N>, M> &graph) {
    if (N != M) {
        std::cout << "\nWrong input passed. Provided array has dimensions " << N
                  << "x" << M << ". Please provide a square matrix.\n";
        return;
    }
    for (int i = 0; i < graph.size(); i++) {
        int min = infinity;
        int minIndex = 0;
        for (int j = 0; j < graph.size(); j++) {
            if (i != j && graph[i][j] != 0 && graph[i][j] < min) {
                min = graph[i][j];
                minIndex = j;
            }
        }
        std::cout << i << "  -  " << minIndex << "\t" << graph[i][minIndex]
                  << "\n";
    }
}
}


static void test() {

    constexpr int INFINITY_INT = std::numeric_limits<int>::max();
    constexpr float INFINITY_FLOAT = std::numeric_limits<float>::max();
    constexpr double INFINITY_DOUBLE = std::numeric_limits<double>::max();
    constexpr uint32_t INFINITY_UINT32 = UINT32_MAX;
  

    std::cout << "\nTest Case 1 :\n";
    std::array<std::array<int, 6>, 6> graph1{
             0,            4,            1,             4,        INFINITY_INT,   INFINITY_INT,
             4,            0,            3,             8,             3,         INFINITY_INT,
             1,            3,            0,        INFINITY_INT,       1,         INFINITY_INT,
             4,            8,       INFINITY_INT,        0,            5,              7,
        INFINITY_INT,      3,            1,              5,            0,         INFINITY_INT,
        INFINITY_INT, INFINITY_INT, INFINITY_INT,        7,       INFINITY_INT,       0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, graph1);


    std::cout << "\nTest Case 2 :\n";
     std::array<std::array<float, 3>, 3> graph2{
             0.0f,           2.5f,  INFINITY_FLOAT,
             2.5f,           0.0f,       3.2f,
        INFINITY_FLOAT,      3.2f,       0.0f};
    greedy_algorithms::findMinimumEdge(INFINITY_FLOAT, graph2);


    std::cout << "\nTest Case 3 :\n";
   std::array<std::array<double, 5>, 5> graph3{
               0.0,             10.5,       INFINITY_DOUBLE,        6.7,              3.3,
               10.5,            0.0,              8.1,              15.4,       INFINITY_DOUBLE,
        INFINITY_DOUBLE,        8.1,              0.0,        INFINITY_DOUBLE,         7.8,
               6.7,             15.4,       INFINITY_DOUBLE,        0.0,               9.9,
               3.3,       INFINITY_DOUBLE,        7.8,              9.9,               0.0};
    greedy_algorithms::findMinimumEdge(INFINITY_DOUBLE, graph3);


    std::cout << "\nTest Case 4 :\n";
    std::array<std::array<int, 3>, 3> graph_neg{
        0,   -2,   4,
       -2,    0,   3,
        4,    3,   0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, graph_neg);


    std::cout << "\nTest Case 5 :\n";
    std::array<std::array<int, 3>, 3> graph_self_loop{
               2,       1, INFINITY_INT,
        INFINITY_INT,   0,        4,
        INFINITY_INT,   4,        0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, graph_self_loop);


    std::cout << "\nTest Case 6 :\n";
    std::array<std::array<int, 4>, 4> no_edges{
               0,       INFINITY_INT,   INFINITY_INT,   INFINITY_INT,
        INFINITY_INT,         0,        INFINITY_INT,   INFINITY_INT,
        INFINITY_INT,   INFINITY_INT,          0,       INFINITY_INT,
        INFINITY_INT,   INFINITY_INT,   INFINITY_INT,           0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, no_edges);


    std::cout << "\nTest Case 7:\n";
    std::array<std::array<int, 4>, 4> partial_graph{
                0,             2,    INFINITY_INT,         6,
                2,             0,            3,     INFINITY_INT,
        INFINITY_INT,          3,            0,             4,
                6,     INFINITY_INT,         4,             0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, partial_graph);



    std::cout << "\nTest Case 8:\n";
    std::array<std::array<int, 4>, 4> directed_graph{
                0,            3,            7,   INFINITY_INT,
        INFINITY_INT,         0,            2,           5,
        INFINITY_INT, INFINITY_INT,         0,           1,
        INFINITY_INT, INFINITY_INT, INFINITY_INT,        0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, directed_graph);


    std::cout << "\nTest Case 9:\n";
   std::array<std::array<int, 4>, 3> graph9{
        0,        5,        5,        5,
        5,        0,        5,        5,        
        5,        5,        5,        5};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, graph9);


    std::cout << "\nTest Case 10:\n";
    std::array<std::array<int, 5>, 5> graph10{
        0,        5,        5,        5,        5,
        5,        0,        5,        5,        5,
        5,        5,        0,        5,        5,
        5,        5,        5,        0,        5,
        5,        5,        5,        5,        0};
    greedy_algorithms::findMinimumEdge(INFINITY_INT, graph10);


    std::cout << "\nTest Case 11 :\n";
    std::array<std::array<uint32_t, 4>, 4> graph_uint32{
                0,                      5,        INFINITY_UINT32,          9,
                5,                      0,                2,        INFINITY_UINT32,
        INFINITY_UINT32,                2,                0,                6,
                9,               INFINITY_UINT32,         6,                0};
    greedy_algorithms::findMinimumEdge(INFINITY_UINT32, graph_uint32);

    std::cout << "\nAll tests have successfully passed!\n";
}



int main() {
    test();
    return 0;
}

