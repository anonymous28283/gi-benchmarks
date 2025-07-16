




double binomial_expected(double n, double p) { return n * p; }


double binomial_variance(double n, double p) { return n * p * (1 - p); }


double binomial_standard_deviation(double n, double p) {
    return std::sqrt(binomial_variance(n, p));
}


double nCr(double n, double r) {
    double numerator = n;
    double denominator = r;

    for (int i = n - 1; i >= ((n - r) + 1); i--) {
        numerator *= i;
    }

    for (int i = 1; i < r; i++) {
        denominator *= i;
    }

    return numerator / denominator;
}


double binomial_x_successes(double n, double p, double x) {
    return nCr(n, x) * std::pow(p, x) * std::pow(1 - p, n - x);
}


double binomial_range_successes(double n, double p, double lower_bound,
                                double upper_bound) {
    double probability = 0;
    for (int i = lower_bound; i <= upper_bound; i++) {
        probability += nCr(n, i) * std::pow(p, i) * std::pow(1 - p, n - i);
    }
    return probability;
}


int main() {
    std::cout << "expected value : " << binomial_expected(100, 0.5)
              << std::endl;

    std::cout << "variance : " << binomial_variance(100, 0.5) << std::endl;

    std::cout << "standard deviation : "
              << binomial_standard_deviation(100, 0.5) << std::endl;

    std::cout << "exactly 30 successes : " << binomial_x_successes(100, 0.5, 30)
              << std::endl;

    std::cout << "45 or more successes : "
              << binomial_range_successes(100, 0.5, 45, 100) << std::endl;

    return 0;
}
