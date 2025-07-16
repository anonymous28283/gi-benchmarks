


















std::complex<double> poly_function(const std::valarray<double> &coeffs,
                                   std::complex<double> x) {
    double real = 0.f, imag = 0.f;
    int n;




    for (n = 0; n < coeffs.size(); n++) {
        std::complex<double> tmp =
            coeffs[n] * std::pow(x, coeffs.size() - n - 1);
        real += tmp.real();
        imag += tmp.imag();
    }

    return std::complex<double>(real, imag);
}


const char *complex_str(const std::complex<double> &x) {

    static char msg[MAX_BUFF_SIZE];

    std::snprintf(msg, MAX_BUFF_SIZE, "% 7.04g%+7.04gj", x.real(), x.imag());

    return msg;
}


bool check_termination(long double delta) {
    static long double past_delta = INFINITY;
    if (std::abs(past_delta - delta) <= ACCURACY || delta < ACCURACY)
        return true;
    past_delta = delta;
    return false;
}


std::pair<uint32_t, double> durand_kerner_algo(
    const std::valarray<double> &coeffs,
    std::valarray<std::complex<double>> *roots, bool write_log = false) {
    long double tol_condition = 1;
    uint32_t iter = 0;
    int n;
    std::ofstream log_file;

    if (write_log) {

        log_file.open("durand_kerner.log.csv");
        if (!log_file.is_open()) {
            perror("Unable to create a storage log file!");
            std::exit(EXIT_FAILURE);
        }
        log_file << "iter#,";

        for (n = 0; n < roots->size(); n++) log_file << "root_" << n << ",";

        log_file << "avg. correction";
        log_file << "\n0,";
        for (n = 0; n < roots->size(); n++)
            log_file << complex_str((*roots)[n]) << ",";
    }

    bool break_loop = false;
    while (!check_termination(tol_condition) && iter < INT16_MAX &&
           !break_loop) {
        tol_condition = 0;
        iter++;
        break_loop = false;

        if (log_file.is_open())
            log_file << "\n" << iter << ",";




        for (n = 0; n < roots->size(); n++) {
            if (break_loop)
                continue;

            std::complex<double> numerator, denominator;
            numerator = poly_function(coeffs, (*roots)[n]);
            denominator = 1.0;
            for (int i = 0; i < roots->size(); i++)
                if (i != n)
                    denominator *= (*roots)[n] - (*roots)[i];

            std::complex<long double> delta = numerator / denominator;

            if (std::isnan(std::abs(delta)) || std::isinf(std::abs(delta))) {
                std::cerr << "\n\nOverflow/underrun error - got value = "
                          << std::abs(delta) << "\n";

                break_loop = true;
            }

            (*roots)[n] -= delta;




            tol_condition = std::max(tol_condition, std::abs(std::abs(delta)));
        }


        if (break_loop)
            break;

        if (log_file.is_open()) {
            for (n = 0; n < roots->size(); n++)
                log_file << complex_str((*roots)[n]) << ",";
        }


        if (iter % 500 == 0) {
            std::cout << "Iter: " << iter << "\t";
            for (n = 0; n < roots->size(); n++)
                std::cout << "\t" << complex_str((*roots)[n]);
            std::cout << "\t\tabsolute average change: " << tol_condition
                      << "\n";
        }


        if (log_file.is_open())
            log_file << tol_condition;
    }

    return std::pair<uint32_t, long double>(iter, tol_condition);
}


void test1() {
    const std::valarray<double> coeffs = {1, 0, 4};
    std::valarray<std::complex<double>> roots(2);
    std::valarray<std::complex<double>> expected = {
        std::complex<double>(0., 2.),
        std::complex<double>(0., -2.)
    };


    for (int n = 0; n < roots.size(); n++) {
        roots[n] = std::complex<double>(std::rand() % 100, std::rand() % 100);
        roots[n] -= 50.f;
        roots[n] /= 25.f;
    }

    auto result = durand_kerner_algo(coeffs, &roots, false);

    for (int i = 0; i < roots.size(); i++) {


        bool err1 = false;
        for (int j = 0; j < roots.size(); j++)
            err1 |= std::abs(std::abs(roots[i] - expected[j])) < 1e-3;
        assert(err1);
    }

    std::cout << "Test 1 passed! - " << result.first << " iterations, "
              << result.second << " accuracy"
              << "\n";
}


void test2() {
    const std::valarray<double> coeffs = {
                                          1. / 64., 0., 0., -1.};
    std::valarray<std::complex<double>> roots(3);
    const std::valarray<std::complex<double>> expected = {
        std::complex<double>(4., 0.), std::complex<double>(-2., 3.46410162),
        std::complex<double>(-2., -3.46410162)
    };


    for (int n = 0; n < roots.size(); n++) {
        roots[n] = std::complex<double>(std::rand() % 100, std::rand() % 100);
        roots[n] -= 50.f;
        roots[n] /= 25.f;
    }

    auto result = durand_kerner_algo(coeffs, &roots, false);

    for (int i = 0; i < roots.size(); i++) {


        bool err1 = false;
        for (int j = 0; j < roots.size(); j++)
            err1 |= std::abs(std::abs(roots[i] - expected[j])) < 1e-3;
        assert(err1);
    }

    std::cout << "Test 2 passed! - " << result.first << " iterations, "
              << result.second << " accuracy"
              << "\n";
}


int main(int argc, char **argv) {

    std::srand(std::time(nullptr));

    if (argc < 2) {
        test1();
        test2();
        std::cout << "Please pass the coefficients of the polynomial as "
                     "commandline "
                     "arguments.\n";
        return 0;
    }

    int n, degree = argc - 1;
    std::valarray<double> coeffs(degree);


    std::valarray<std::complex<double>> s0(degree - 1);

    std::cout << "Computing the roots for:\n\t";
    for (n = 0; n < degree; n++) {
        coeffs[n] = strtod(argv[n + 1], nullptr);
        if (n < degree - 1 && coeffs[n] != 0)
            std::cout << "(" << coeffs[n] << ") x^" << degree - n - 1 << " + ";
        else if (coeffs[n] != 0)
            std::cout << "(" << coeffs[n] << ") x^" << degree - n - 1
                      << " = 0\n";


        if (n < degree - 1) {
            s0[n] = std::complex<double>(std::rand() % 100, std::rand() % 100);
            s0[n] -= 50.f;
            s0[n] /= 50.f;
        }
    }



    {
        double tmp = coeffs[0];
        coeffs /= tmp;
    }

    clock_t end_time, start_time = clock();
    auto result = durand_kerner_algo(coeffs, &s0, true);
    end_time = clock();

    std::cout << "\nIterations: " << result.first << "\n";
    for (n = 0; n < degree - 1; n++)
        std::cout << "\t" << complex_str(s0[n]) << "\n";
    std::cout << "absolute average change: " << result.second << "\n";
    std::cout << "Time taken: "
              << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC
              << " sec\n";

    return 0;
}
