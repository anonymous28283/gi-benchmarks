








namespace math {

void sieve(std::vector<bool> *vec) {
    (*vec)[0] = false;
    (*vec)[1] = false;


    for (uint64_t n = 2; n < vec->size(); n++) {
        for (uint64_t multiple = n << 1; multiple < vec->size();
             multiple += n) {
            (*vec)[multiple] = false;
        }
    }
}


void print_primes(std::vector<bool> const &primes) {
    for (uint64_t i = 0; i < primes.size(); i++) {
        if (primes[i]) {
            std::cout << i << std::endl;
        }
    }
}
}


static void test() {
    auto primes = std::vector<bool>(10, true);
    math::sieve(&primes);
    assert(primes[0] == false);
    assert(primes[1] == false);
    assert(primes[2] == true);
    assert(primes[3] == true);
    assert(primes[4] == false);
    assert(primes[5] == true);
    assert(primes[6] == false);
    assert(primes[7] == true);
    assert(primes[8] == false);
    assert(primes[9] == false);

    std::cout << "All tests have successfully passed!\n";
}


int main(int argc, char *argv[]) {
    test();


    auto max = 10000;



    auto primes = std::vector<bool>(max, true);


    auto start = std::chrono::high_resolution_clock::now();


    math::sieve(&primes);


    auto time = std::chrono::duration_cast<
                    std::chrono::duration<double, std::ratio<1>>>(
                    std::chrono::high_resolution_clock::now() - start)
                    .count();


    if (argc > 1 && argv[1] == std::string("print")) {
        math::print_primes(primes);
    }


    std::cout << "Time taken: " << time << " seconds" << std::endl;

    return 0;
}
