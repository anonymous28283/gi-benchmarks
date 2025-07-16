






namespace math {

namespace n_bonacci {

std::vector<uint64_t> N_bonacci(const uint64_t &n, const uint64_t &m) {
    std::vector<uint64_t> a(
        m, 0);
    if (m < n || n == 0) {
        return a;
    }

    a[n - 1] = 1;

    if (n == m) {
        return a;
    }
    a[n] = 1;

    for (uint64_t i = n + 1; i < m; i++) {



        a[i] = 2 * a[i - 1] - a[i - 1 - n];
    }
    return a;
}
}
}


static void test() {
    struct TestCase {
        const uint64_t n;
        const uint64_t m;
        const std::vector<uint64_t> expected;
        TestCase(const uint64_t in_n, const uint64_t in_m,
                 std::initializer_list<uint64_t> data)
            : n(in_n), m(in_m), expected(data) {
            assert(data.size() == m);
        }
    };
    const std::vector<TestCase> test_cases = {
        TestCase(0, 0, {}),
        TestCase(0, 1, {0}),
        TestCase(0, 2, {0, 0}),
        TestCase(1, 0, {}),
        TestCase(1, 1, {1}),
        TestCase(1, 2, {1, 1}),
        TestCase(1, 3, {1, 1, 1}),
        TestCase(5, 15, {0, 0, 0, 0, 1, 1, 2, 4, 8, 16, 31, 61, 120, 236, 464}),
        TestCase(
            6, 17,
            {0, 0, 0, 0, 0, 1, 1, 2, 4, 8, 16, 32, 63, 125, 248, 492, 976}),
        TestCase(56, 15, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})};

    for (const auto &tc : test_cases) {
        assert(math::n_bonacci::N_bonacci(tc.n, tc.m) == tc.expected);
    }
    std::cout << "passed" << std::endl;
}


int main() {
    test();
    return 0;
}
