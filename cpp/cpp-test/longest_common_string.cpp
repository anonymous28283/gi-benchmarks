








std::size_t longest_common_string_length(const std::string& string_a,
                                         const std::string& string_b) {
    const auto size_a = string_a.size();
    const auto size_b = string_b.size();
    std::vector<std::vector<std::size_t>> sub_sols(
        size_a + 1, std::vector<std::size_t>(size_b + 1, 0));

    const auto limit = static_cast<std::size_t>(-1);
    for (std::size_t pos_a = size_a - 1; pos_a != limit; --pos_a) {
        for (std::size_t pos_b = size_b - 1; pos_b != limit; --pos_b) {
            if (string_a[pos_a] == string_b[pos_b]) {
                sub_sols[pos_a][pos_b] = 1 + sub_sols[pos_a + 1][pos_b + 1];
            } else {
                sub_sols[pos_a][pos_b] = std::max(sub_sols[pos_a + 1][pos_b],
                                                  sub_sols[pos_a][pos_b + 1]);
            }
        }
    }

    return sub_sols[0][0];
}


struct TestCase {
    const std::string string_a;
    const std::string string_b;
    const std::size_t common_string_len;

    TestCase(std::string string_a, std::string string_b,
             const std::size_t in_common_string_len)
        : string_a(std::move(string_a)),
          string_b(std::move(string_b)),
          common_string_len(in_common_string_len) {}
};


std::vector<TestCase> get_test_cases() {
    return {TestCase("", "", 0),
            TestCase("ab", "ab", 2),
            TestCase("ab", "ba", 1),
            TestCase("", "xyz", 0),
            TestCase("abcde", "ace", 3),
            TestCase("BADANA", "ANADA", 3),
            TestCase("BADANA", "CANADAS", 3),
            TestCase("a1a234a5aaaa6", "A1AAAA234AAA56AAAAA", 6),
            TestCase("123x", "123", 3),
            TestCase("12x3x", "123", 3),
            TestCase("1x2x3x", "123", 3),
            TestCase("x1x2x3x", "123", 3),
            TestCase("x12x3x", "123", 3)};
}


template <typename TestCases>
static void test_longest_common_string_length(const TestCases& test_cases) {
    for (const auto& cur_tc : test_cases) {
        assert(longest_common_string_length(cur_tc.string_a, cur_tc.string_b) ==
               cur_tc.common_string_len);
    }
}


template <typename TestCases>
static void test_longest_common_string_length_is_symmetric(
    const TestCases& test_cases) {
    for (const auto& cur_tc : test_cases) {
        assert(longest_common_string_length(cur_tc.string_b, cur_tc.string_a) ==
               cur_tc.common_string_len);
    }
}


std::string reverse_str(const std::string& in_str) {
    return {in_str.rbegin(), in_str.rend()};
}


template <typename TestCases>
static void test_longest_common_string_length_for_reversed_inputs(
    const TestCases& test_cases) {
    for (const auto& cur_tc : test_cases) {
        assert(longest_common_string_length(reverse_str(cur_tc.string_a),
                                            reverse_str(cur_tc.string_b)) ==
               cur_tc.common_string_len);
    }
}


static void tests() {
    const auto test_cases = get_test_cases();
    assert(test_cases.size() > 0);
    test_longest_common_string_length(test_cases);
    test_longest_common_string_length_is_symmetric(test_cases);
    test_longest_common_string_length_for_reversed_inputs(test_cases);

    std::cout << "All tests have successfully passed!\n";
}


int main() {
    tests();
    return 0;
}
