











double get_minima(const std::function<double(double)> &f, double lim_a,
                  double lim_b) {
    uint32_t iters = 0;
    double c, d;
    double prev_mean, mean = std::numeric_limits<double>::infinity();


    const double M_GOLDEN_RATIO = (1.f + std::sqrt(5.f)) / 2.f;


    if (lim_a > lim_b) {
        std::swap(lim_a, lim_b);
    } else if (std::abs(lim_a - lim_b) <= EPSILON) {
        std::cerr << "Search range must be greater than " << EPSILON << "\n";
        return lim_a;
    }

    do {
        prev_mean = mean;


        double ratio = (lim_b - lim_a) / M_GOLDEN_RATIO;
        c = lim_b - ratio;
        d = lim_a + ratio;

        if (f(c) < f(d)) {

            lim_b = d;
        } else {

            lim_a = c;
        }

        mean = (lim_a + lim_b) / 2.f;
        iters++;


    } while (std::abs(lim_a - lim_b) > EPSILON);

    std::cout << " (iters: " << iters << ") ";
    return prev_mean;
}


void test1() {

    std::function<double(double)> f1 = [](double x) {
        return (x - 2) * (x - 2);
    };

    std::cout << "Test 1.... ";

    double minima = get_minima(f1, 1, 5);

    std::cout << minima << "...";

    assert(std::abs(minima - 2) < EPSILON);
    std::cout << "passed\n";
}


void test2() {


    std::function<double(double)> func = [](double x) {
        return -std::pow(x, 1.f / x);
    };

    std::cout << "Test 2.... ";

    double minima = get_minima(func, -2, 10);

    std::cout << minima << " (" << M_E << ")...";

    assert(std::abs(minima - M_E) < EPSILON);
    std::cout << "passed\n";
}


void test3() {


    std::function<double(double)> func = [](double x) { return std::cos(x); };

    std::cout << "Test 3.... ";

    double minima = get_minima(func, -4, 12);

    std::cout << minima << " (" << M_PI << ")...";

    assert(std::abs(minima - M_PI) < EPSILON);
    std::cout << "passed\n";
}


int main() {
    std::cout.precision(9);

    std::cout << "Computations performed with machine epsilon: " << EPSILON
              << "\n";

    test1();
    test2();
    test3();

    return 0;
}
