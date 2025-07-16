







namespace math {

namespace fibonacci_sum {
using matrix = std::vector<std::vector<uint64_t> >;


math::fibonacci_sum::matrix multiply(const math::fibonacci_sum::matrix &T,
                                     const math::fibonacci_sum::matrix &A) {
    math::fibonacci_sum::matrix result(2, std::vector<uint64_t>(2, 0));


    result[0][0] = T[0][0] * A[0][0] + T[0][1] * A[1][0];
    result[0][1] = T[0][0] * A[0][1] + T[0][1] * A[1][1];
    result[1][0] = T[1][0] * A[0][0] + T[1][1] * A[1][0];
    result[1][1] = T[1][0] * A[0][1] + T[1][1] * A[1][1];

    return result;
}


math::fibonacci_sum::matrix power(math::fibonacci_sum::matrix T, uint64_t ex) {
    math::fibonacci_sum::matrix A{{1, 1}, {1, 0}};
    if (ex == 0 || ex == 1) {
        return T;
    }

    T = power(T, ex / 2);
    T = multiply(T, T);
    if (ex & 1) {
        T = multiply(T, A);
    }
    return T;
}


uint64_t result(uint64_t n) {
    math::fibonacci_sum::matrix T{{1, 1}, {1, 0}};
    T = power(T, n);
    uint64_t ans = T[0][1];
    ans = (ans - 1);
    return ans;
}


uint64_t fiboSum(uint64_t n, uint64_t m) {
    return (result(m + 2) - result(n + 1));
}
}
}


static void test() {
    uint64_t n = 0, m = 3;
    uint64_t test_1 = math::fibonacci_sum::fiboSum(n, m);
    assert(test_1 == 4);
    std::cout << "Passed Test 1!" << std::endl;

    n = 3;
    m = 5;
    uint64_t test_2 = math::fibonacci_sum::fiboSum(n, m);
    assert(test_2 == 10);
    std::cout << "Passed Test 2!" << std::endl;

    n = 5;
    m = 7;
    uint64_t test_3 = math::fibonacci_sum::fiboSum(n, m);
    assert(test_3 == 26);
    std::cout << "Passed Test 3!" << std::endl;

    n = 7;
    m = 10;
    uint64_t test_4 = math::fibonacci_sum::fiboSum(n, m);
    assert(test_4 == 123);
    std::cout << "Passed Test 4!" << std::endl;

    n = 9;
    m = 12;
    uint64_t test_5 = math::fibonacci_sum::fiboSum(n, m);
    assert(test_5 == 322);
    std::cout << "Passed Test 5!" << std::endl;
}


int main() {
    test();
    return 0;
}
