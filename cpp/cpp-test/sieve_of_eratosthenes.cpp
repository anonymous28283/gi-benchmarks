







namespace math {

namespace sieve_of_eratosthenes {

std::vector<bool> sieve(uint32_t N) {
    std::vector<bool> is_prime(N + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (uint32_t i = 2; i * i <= N; i++) {
        if (is_prime[i]) {
            for (uint32_t j = i * i; j <= N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}


void print(uint32_t N, const std::vector<bool> &is_prime) {
    for (uint32_t i = 2; i <= N; i++) {
        if (is_prime[i]) {
            std::cout << i << ' ';
        }
    }
    std::cout << std::endl;
}

}
}


static void tests() {
    std::vector<bool> is_prime_1 =
        math::sieve_of_eratosthenes::sieve(static_cast<uint32_t>(10));
    std::vector<bool> is_prime_2 =
        math::sieve_of_eratosthenes::sieve(static_cast<uint32_t>(20));
    std::vector<bool> is_prime_3 =
        math::sieve_of_eratosthenes::sieve(static_cast<uint32_t>(100));

    std::vector<bool> expected_1{false, false, true,  true,  false, true,
                                 false, true,  false, false, false};
    assert(is_prime_1 == expected_1);

    std::vector<bool> expected_2{false, false, true,  true,  false, true,
                                 false, true,  false, false, false, true,
                                 false, true,  false, false, false, true,
                                 false, true,  false};
    assert(is_prime_2 == expected_2);

    std::vector<bool> expected_3{
        false, false, true,  true,  false, true,  false, true,  false, false,
        false, true,  false, true,  false, false, false, true,  false, true,
        false, false, false, true,  false, false, false, false, false, true,
        false, true,  false, false, false, false, false, true,  false, false,
        false, true,  false, true,  false, false, false, true,  false, false,
        false, false, false, true,  false, false, false, false, false, true,
        false, true,  false, false, false, false, false, true,  false, false,
        false, true,  false, true,  false, false, false, false, false, true,
        false, false, false, true,  false, false, false, false, false, true,
        false, false, false, false, false, false, false, true,  false, false,
        false};
    assert(is_prime_3 == expected_3);

}


int main() {
    tests();
    return 0;
}
