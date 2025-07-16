











namespace numerical_methods {

namespace simpson_method {

double evaluate_by_simpson(std::int32_t N, double h, double a,
                           const std::function<double(double)>& func) {
    std::map<std::int32_t, double>
        data_table;
    double xi = a;


    double temp = NAN;
    for (std::int32_t i = 0; i <= N; i++) {
        temp = func(xi);
        data_table.insert(
            std::pair<std::int32_t, double>(i, temp));
        xi += h;
    }



    double evaluate_integral = 0;
    for (std::int32_t i = 0; i <= N; i++) {
        if (i == 0 || i == N) {
            evaluate_integral += data_table.at(i);
        } else if (i % 2 == 1) {
            evaluate_integral += 4 * data_table.at(i);
        } else {
            evaluate_integral += 2 * data_table.at(i);
        }
    }


    evaluate_integral *= h / 3;



    assert(!std::isnan(evaluate_integral) &&
           "The definite integral can't be evaluated. Check the validity of "
           "your input.\n");

    return evaluate_integral;
}


double f(double x) { return std::sqrt(x) + std::log(x); }

double g(double x) { return std::exp(-x) * (4 - std::pow(x, 2)); }

double k(double x) { return std::sqrt(2 * std::pow(x, 3) + 3); }

double l(double x) { return x + std::log(2 * x + 1); }
}
}


static void test(std::int32_t N, double h, double a, double b,
                 bool used_argv_parameters) {

    double result_f = numerical_methods::simpson_method::evaluate_by_simpson(
        N, h, a, numerical_methods::simpson_method::f);
    assert((used_argv_parameters || (result_f >= 4.09 && result_f <= 4.10)) &&
           "The result of f(x) is wrong");
    std::cout << "The result of integral f(x) on interval [" << a << ", " << b
              << "] is equal to: " << result_f << std::endl;

    double result_g = numerical_methods::simpson_method::evaluate_by_simpson(
        N, h, a, numerical_methods::simpson_method::g);
    assert((used_argv_parameters || (result_g >= 0.27 && result_g <= 0.28)) &&
           "The result of g(x) is wrong");
    std::cout << "The result of integral g(x) on interval [" << a << ", " << b
              << "] is equal to: " << result_g << std::endl;

    double result_k = numerical_methods::simpson_method::evaluate_by_simpson(
        N, h, a, numerical_methods::simpson_method::k);
    assert((used_argv_parameters || (result_k >= 9.06 && result_k <= 9.07)) &&
           "The result of k(x) is wrong");
    std::cout << "The result of integral k(x) on interval [" << a << ", " << b
              << "] is equal to: " << result_k << std::endl;

    double result_l = numerical_methods::simpson_method::evaluate_by_simpson(
        N, h, a, numerical_methods::simpson_method::l);
    assert((used_argv_parameters || (result_l >= 7.16 && result_l <= 7.17)) &&
           "The result of l(x) is wrong");
    std::cout << "The result of integral l(x) on interval [" << a << ", " << b
              << "] is equal to: " << result_l << std::endl;
}


int main(int argc, char** argv) {
    std::int32_t N = 16;

    double a = 1, b = 3;

    double h = NAN;

    bool used_argv_parameters =
        false;




    if (argc == 4) {
        N = std::atoi(argv[1]);
        a = std::atof(argv[2]);
        b = std::atof(argv[3]);

        assert(a < b && "a has to be less than b");
        assert(N > 0 && "N has to be > 0");
        if (N < 16 || a != 1 || b != 3) {
            used_argv_parameters = true;
        }
        std::cout << "You selected N=" << N << ", a=" << a << ", b=" << b
                  << std::endl;
    } else {
        std::cout << "Default N=" << N << ", a=" << a << ", b=" << b
                  << std::endl;
    }


    h = (b - a) / N;

    test(N, h, a, b, used_argv_parameters);

    return 0;
}
