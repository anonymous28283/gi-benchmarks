







bool test1() {
    std::cout << "---- Check 1\t";
    unsigned int i, number = 10;
    large_number result;
    for (i = 2; i <= number; i++)
        result *= i;

    const char *known_reslt = "3628800";


    if (strlen(known_reslt) != result.num_digits()) {
        std::cerr << "Result lengths dont match! " << strlen(known_reslt)
                  << " != " << result.num_digits() << std::endl;
        return false;
    }

    const size_t N = result.num_digits();
    for (i = 0; i < N; i++) {
        if (known_reslt[i] != result.digit_char(i)) {
            std::cerr << i << "^th digit mismatch! " << known_reslt[i]
                      << " != " << result.digit_char(i) << std::endl;
            return false;
        }
    }

    std::cout << "Passed!" << std::endl;
    return true;
}


bool test2() {
    std::cout << "---- Check 2\t";
    unsigned int i, number = 100;
    large_number result;
    for (i = 2; i <= number; i++)
        result *= i;

    const char *known_reslt =
        "9332621544394415268169923885626670049071596826438162146859296389521759"
        "9993229915608941463976156518286253697920827223758251185210916864000000"
        "000000000000000000";


    if (strlen(known_reslt) != result.num_digits()) {
        std::cerr << "Result lengths dont match! " << strlen(known_reslt)
                  << " != " << result.num_digits() << std::endl;
        return false;
    }

    const size_t N = result.num_digits();
    for (i = 0; i < N; i++) {
        if (known_reslt[i] != result.digit_char(i)) {
            std::cerr << i << "^th digit mismatch! " << known_reslt[i]
                      << " != " << result.digit_char(i) << std::endl;
            return false;
        }
    }

    std::cout << "Passed!" << std::endl;
    return true;
}


int main(int argc, char *argv[]) {
    int number, i;

    if (argc == 2) {
        number = atoi(argv[1]);
    } else {
        std::cout << "Enter the value of n(n starts from 0 ): ";
        std::cin >> number;
    }

    large_number result;

    std::clock_t start_time = std::clock();
    for (i = 2; i <= number; i++)
        result *= i;
    std::clock_t end_time = std::clock();
    double time_taken =
        static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

    std::cout << number << "! = " << result << std::endl
              << "Number of digits: " << result.num_digits() << std::endl
              << "Time taken: " << std::scientific << time_taken << " s"
              << std::endl;

    test1();
    test2();
    result.test();

    return 0;
}
