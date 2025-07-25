








namespace probability {

namespace geometric_dist {

double exponential_expected(double lambda) {
    if (lambda <= 0) {
        throw std::invalid_argument("lambda must be greater than 0");
    }
    return 1 / lambda;
}


double exponential_var(double lambda) {
    if (lambda <= 0) {
        throw std::invalid_argument("lambda must be greater than 0");
    }
    return 1 / pow(lambda, 2);
}


double exponential_std(double lambda) {
    if (lambda <= 0) {
        throw std::invalid_argument("lambda must be greater than 0");
    }
    return 1 / lambda;
}
}
}


static void test() {
    double lambda_1 = 1;
    double expected_1 = 1;
    double var_1 = 1;
    double std_1 = 1;

    double lambda_2 = 2;
    double expected_2 = 0.5;
    double var_2 = 0.25;
    double std_2 = 0.5;

    double lambda_3 = 3;
    double expected_3 = 0.333333;
    double var_3 = 0.111111;
    double std_3 = 0.333333;

    double lambda_4 = 0;
    double lambda_5 = -2.3;

    const float threshold = 1e-3f;

    std::cout << "Test for lambda = 1 \n";
    assert(
        std::abs(expected_1 - probability::geometric_dist::exponential_expected(
                                  lambda_1)) < threshold);
    assert(std::abs(var_1 - probability::geometric_dist::exponential_var(
                                lambda_1)) < threshold);
    assert(std::abs(std_1 - probability::geometric_dist::exponential_std(
                                lambda_1)) < threshold);
    std::cout << "ALL TEST PASSED\n\n";

    std::cout << "Test for lambda = 2 \n";
    assert(
        std::abs(expected_2 - probability::geometric_dist::exponential_expected(
                                  lambda_2)) < threshold);
    assert(std::abs(var_2 - probability::geometric_dist::exponential_var(
                                lambda_2)) < threshold);
    assert(std::abs(std_2 - probability::geometric_dist::exponential_std(
                                lambda_2)) < threshold);
    std::cout << "ALL TEST PASSED\n\n";

    std::cout << "Test for lambda = 3 \n";
    assert(
        std::abs(expected_3 - probability::geometric_dist::exponential_expected(
                                  lambda_3)) < threshold);
    assert(std::abs(var_3 - probability::geometric_dist::exponential_var(
                                lambda_3)) < threshold);
    assert(std::abs(std_3 - probability::geometric_dist::exponential_std(
                                lambda_3)) < threshold);
    std::cout << "ALL TEST PASSED\n\n";

    std::cout << "Test for lambda = 0 \n";
    try {
        probability::geometric_dist::exponential_expected(lambda_4);
        probability::geometric_dist::exponential_var(lambda_4);
        probability::geometric_dist::exponential_std(lambda_4);
    } catch (std::invalid_argument& err) {
        assert(std::string(err.what()) == "lambda must be greater than 0");
    }
    std::cout << "ALL TEST PASSED\n\n";

    std::cout << "Test for lambda = -2.3 \n";
    try {
        probability::geometric_dist::exponential_expected(lambda_5);
        probability::geometric_dist::exponential_var(lambda_5);
        probability::geometric_dist::exponential_std(lambda_5);
    } catch (std::invalid_argument& err) {
        assert(std::string(err.what()) == "lambda must be greater than 0");
    }
    std::cout << "ALL TEST PASSED\n\n";
}


int main() {
    test();
    return 0;
}
