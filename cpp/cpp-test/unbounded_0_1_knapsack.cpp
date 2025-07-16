







namespace dynamic_programming {


namespace unbounded_knapsack {


std::uint16_t KnapSackFilling(std::uint16_t i, std::uint16_t W,
                              const std::vector<std::uint16_t>& val,
                              const std::vector<std::uint16_t>& wt,
                              std::vector<std::vector<int>>& dp) {
    if (i == 0) {
        if (wt[0] <= W) {
            return (W / wt[0]) *
                   val[0];
        } else {
            return 0;
        }
    }
    if (dp[i][W] != -1)
        return dp[i][W];

    int nottake =
        KnapSackFilling(i - 1, W, val, wt, dp);
    int take = 0;
    if (W >= wt[i]) {
        take = val[i] + KnapSackFilling(i, W - wt[i], val, wt,
                                        dp);
    }
    return dp[i][W] =
               std::max(take, nottake);
}


std::uint16_t unboundedKnapsack(std::uint16_t N, std::uint16_t W,
                                const std::vector<std::uint16_t>& val,
                                const std::vector<std::uint16_t>& wt) {
    if (N == 0)
        return 0;
    std::vector<std::vector<int>> dp(
        N, std::vector<int>(W + 1, -1));
    return KnapSackFilling(N - 1, W, val, wt, dp);
}

}

}


static void tests() {

    std::uint16_t N1 = 4;
    std::vector<std::uint16_t> wt1 = {1, 3, 4, 5};
    std::vector<std::uint16_t> val1 = {6, 1, 7, 7};
    std::uint16_t W1 = 8;

    assert(dynamic_programming::unbounded_knapsack::unboundedKnapsack(
               N1, W1, val1, wt1) == 48);
    std::cout << "Maximum Knapsack value "
              << dynamic_programming::unbounded_knapsack::unboundedKnapsack(
                     N1, W1, val1, wt1)
              << std::endl;


    std::uint16_t N2 = 3;
    std::vector<std::uint16_t> wt2 = {10, 20, 30};
    std::vector<std::uint16_t> val2 = {60, 100, 120};
    std::uint16_t W2 = 5;

    assert(dynamic_programming::unbounded_knapsack::unboundedKnapsack(
               N2, W2, val2, wt2) == 0);
    std::cout << "Maximum Knapsack value "
              << dynamic_programming::unbounded_knapsack::unboundedKnapsack(
                     N2, W2, val2, wt2)
              << std::endl;


    std::uint16_t N3 = 3;
    std::vector<std::uint16_t> wt3 = {2, 4, 6};
    std::vector<std::uint16_t> val3 = {5, 11, 13};
    std::uint16_t W3 = 27;

    assert(dynamic_programming::unbounded_knapsack::unboundedKnapsack(
               N3, W3, val3, wt3) == 27);
    std::cout << "Maximum Knapsack value "
              << dynamic_programming::unbounded_knapsack::unboundedKnapsack(
                     N3, W3, val3, wt3)
              << std::endl;


    std::uint16_t N4 = 0;
    std::vector<std::uint16_t> wt4 = {};
    std::vector<std::uint16_t> val4 = {};
    std::uint16_t W4 = 10;
    assert(dynamic_programming::unbounded_knapsack::unboundedKnapsack(
               N4, W4, val4, wt4) == 0);
    std::cout << "Maximum Knapsack value for empty arrays: "
              << dynamic_programming::unbounded_knapsack::unboundedKnapsack(
                     N4, W4, val4, wt4)
              << std::endl;

    std::cout << "All test cases passed!" << std::endl;
}


int main() {
    tests();
    return 0;
}
