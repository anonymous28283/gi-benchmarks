







namespace dynamic_programming {

namespace house_robber {

std::uint32_t houseRobber(const std::vector<uint32_t> &money,
                          const uint32_t &n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return money[0];
    }
    if (n == 2) {

        return std::max(money[0], money[1]);
    }
    uint32_t max_value = 0;
    uint32_t value1 = money[0];
    uint32_t value2 = std::max(money[0], money[1]);
    for (uint32_t i = 2; i < n; i++) {
        max_value = std::max(money[i] + value1, value2);
        value1 = value2;
        value2 = max_value;
    }

    return max_value;
}
}
}


static void test() {


    std::vector<uint32_t> array1 = {1, 2, 3, 1};
    std::cout << "Test 1... ";
    assert(
        dynamic_programming::house_robber::houseRobber(array1, array1.size()) ==
        4);

    std::cout << "passed" << std::endl;



    std::vector<uint32_t> array2 = {6, 7, 1, 3, 8, 2, 4};
    std::cout << "Test 2... ";
    assert(
        dynamic_programming::house_robber::houseRobber(array2, array2.size()) ==
        19);

    std::cout << "passed" << std::endl;



    std::vector<uint32_t> array3 = {};
    std::cout << "Test 3... ";
    assert(
        dynamic_programming::house_robber::houseRobber(array3, array3.size()) ==
        0);
    std::cout << "passed" << std::endl;



    std::vector<uint32_t> array4 = {2, 7, 9, 3, 1};
    std::cout << "Test 4... ";
    assert(
        dynamic_programming::house_robber::houseRobber(array4, array4.size()) ==
        12);

    std::cout << "passed" << std::endl;
}


int main() {
    test();
    return 0;
}
