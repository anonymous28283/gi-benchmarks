




double poisson_rate(double events, double timeframe) {
    return events / timeframe;
}


double poisson_expected(double rate, double time) { return rate * time; }


double fact(double x) {
    double x_fact = x;
    for (int i = x - 1; i > 0; i--) {
        x_fact *= i;
    }

    if (x_fact <= 0) {
        x_fact = 1;
    }
    return x_fact;
}


double poisson_x_successes(double expected, double x) {
    return (std::pow(expected, x) * std::exp(-expected)) / fact(x);
}


double poisson_range_successes(double expected, double lower, double upper) {
    double probability = 0;
    for (int i = lower; i <= upper; i++) {
        probability += poisson_x_successes(expected, i);
    }
    return probability;
}


int main() {
    double rate, expected;
    rate = poisson_rate(3, 1);
    std::cout << "Poisson rate : " << rate << std::endl;

    expected = poisson_expected(rate, 2);
    std::cout << "Poisson expected : " << expected << std::endl;

    std::cout << "Poisson 0 successes : " << poisson_x_successes(expected, 0)
              << std::endl;
    std::cout << "Poisson 0-8 successes : "
              << poisson_range_successes(expected, 0, 8) << std::endl;

    return 0;
}
