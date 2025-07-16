







namespace math {


uint64_t iterativeFactorial(uint8_t n) {
    if (n > 20) {
        throw std::invalid_argument("Maximum n value is 20");
    }


    uint64_t accumulator = 1;

    while (n > 1) {
        accumulator *= n;
        --n;
    }

    return accumulator;
}

}


static void test() {

    std::cout << "Exception case test \n"
                 "Input: 0 \n"
                 "Expected output: 1 \n\n";
    assert(math::iterativeFactorial(0) == 1);


    std::cout << "Base case test \n"
                 "Input: 1 \n"
                 "Expected output: 1 \n\n";
    assert(math::iterativeFactorial(1) == 1);


    std::cout << "Small number case test \n"
                 "Input: 5 \n"
                 "Expected output: 120 \n\n";
    assert(math::iterativeFactorial(5) == 120);


    std::cout << "Medium number case test \n"
                 "Input: 10 \n"
                 "Expected output: 3628800 \n\n";
    assert(math::iterativeFactorial(10) == 3628800);


    std::cout << "Maximum case test \n"
                 "Input: 20 \n"
                 "Expected output: 2432902008176640000\n\n";
    assert(math::iterativeFactorial(20) == 2432902008176640000);


    std::cout << "Exception test \n"
                 "Input: 21 \n"
                 "Expected output: Exception thrown \n";

    bool wasExceptionThrown = false;
    try {
        math::iterativeFactorial(21);
    } catch (const std::invalid_argument&) {
        wasExceptionThrown = true;
    }
    assert(wasExceptionThrown);

    std::cout << "All tests have passed successfully.\n";
}


int main() {
    test();
    return 0;
}
