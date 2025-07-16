






namespace math {

namespace modular_division {

uint64_t power(uint64_t a, uint64_t b, uint64_t c) {
    uint64_t ans = 1;
    a = a % c;
    if (a == 0) {
        return 0;
    }
    while (b > 0) {

        if (b & 1) {
            ans = ((ans % c) * (a % c)) % c;
        }

        b = b >> 1;
        a = ((a % c) * (a % c)) % c;
    }
    return ans;
}


uint64_t mod_division(uint64_t a, uint64_t b, uint64_t p) {
    uint64_t inverse = power(b, p - 2, p) % p;
    uint64_t result =
        ((a % p) * (inverse % p)) % p;
    return result;
}
}
}


static void test() {
    uint64_t test_case_1 = math::modular_division::mod_division(8, 2, 2);
    assert(test_case_1 == 0);
    std::cout << "Test 1 Passed!" << std::endl;
    uint64_t test_case_2 = math::modular_division::mod_division(15, 3, 7);
    assert(test_case_2 == 5);
    std::cout << "Test 2 Passed!" << std::endl;
    uint64_t test_case_3 = math::modular_division::mod_division(10, 5, 2);
    assert(test_case_3 == 0);
    std::cout << "Test 3 Passed!" << std::endl;
    uint64_t test_case_4 = math::modular_division::mod_division(81, 3, 5);
    assert(test_case_4 == 2);
    std::cout << "Test 4 Passed!" << std::endl;
    uint64_t test_case_5 = math::modular_division::mod_division(12848, 73, 29);
    assert(test_case_5 == 2);
    std::cout << "Test 5 Passed!" << std::endl;
}


int main(int argc, char *argv[]) {
    test();
    return 0;
}
