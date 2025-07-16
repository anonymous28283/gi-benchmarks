







namespace dynamic_programming {

namespace cut_rod {

template <size_t T>
int maxProfitByCuttingRod(const std::array<int, T> &price, const uint64_t &n) {
    int *profit =
        new int[n + 1];

    profit[0] = 0;




    for (size_t i = 1; i <= n; i++) {
        int q = INT_MIN;
        for (size_t j = 1; j <= i; j++) {
            q = std::max(q, price[j - 1] + profit[i - j]);
        }
        profit[i] = q;
    }
    const int16_t ans = profit[n];
    delete[] profit;
    return ans;
}
}
}


static void test() {

    const int16_t n1 = 8;
    std::array<int32_t, n1> price1 = {1, 2, 4, 6, 8, 45, 21, 9};
    const int64_t max_profit1 =
        dynamic_programming::cut_rod::maxProfitByCuttingRod(price1, n1);
    const int64_t expected_max_profit1 = 47;
    assert(max_profit1 == expected_max_profit1);
    std::cout << "Maximum profit with " << n1 << " inch road is " << max_profit1
              << std::endl;


    const int16_t n2 = 30;
    std::array<int32_t, n2> price2 = {
        1,  5,  8,  9,  10, 17, 17, 20, 24, 30,
        31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50};

    const int64_t max_profit2 =
        dynamic_programming::cut_rod::maxProfitByCuttingRod(price2, n2);
    const int32_t expected_max_profit2 = 90;
    assert(max_profit2 == expected_max_profit2);
    std::cout << "Maximum profit with " << n2 << " inch road is " << max_profit2
              << std::endl;

    const int16_t n3 = 5;
    std::array<int32_t, n3> price3 = {2, 9, 17, 23, 45};
    const int64_t max_profit3 =
        dynamic_programming::cut_rod::maxProfitByCuttingRod(price3, n3);
    const int64_t expected_max_profit3 = 45;
    assert(max_profit3 == expected_max_profit3);
    std::cout << "Maximum profit with " << n3 << " inch road is " << max_profit3
              << std::endl;
}


int main() {

    test();
    return 0;
}
