









double get_minima(const std::function<double(double)> &f, double lim_a,
                  double lim_b) {
    uint32_t iters = 0;

    if (lim_a > lim_b) {
        std::swap(lim_a, lim_b);
    } else if (std::abs(lim_a - lim_b) <= EPSILON) {
        std::cerr << "Search range must be greater than " << EPSILON << "\n";
        return lim_a;
    }


    const double M_GOLDEN_RATIO = (3.f - std::sqrt(5.f)) / 2.f;

    double v = lim_a + M_GOLDEN_RATIO * (lim_b - lim_a);
    double u, w = v, x = v;
    double fu, fv = f(v);
    double fw = fv, fx = fv;

    double mid_point = (lim_a + lim_b) / 2.f;
    double p = 0, q = 0, r = 0;

    double d, e = 0;
    double tolerance, tolerance2;

    do {
        mid_point = (lim_a + lim_b) / 2.f;
        tolerance = EPSILON * std::abs(x);
        tolerance2 = 2 * tolerance;

        if (std::abs(e) > tolerance2) {

            r = (x - w) * (fx - fv);
            q = (x - v) * (fx - fw);
            p = (x - v) * q - (x - w) * r;
            q = 2.f * (q - r);
            if (q > 0)
                p = -p;
            else
                q = -q;
            r = e;
            e = d;
        }

        if (std::abs(p) < std::abs(0.5 * q * r) && p < q * (lim_b - x)) {

            d = p / q;
            u = x + d;
            if (u - lim_a < tolerance2 || lim_b - u < tolerance2)
                d = x < mid_point ? tolerance : -tolerance;
        } else {

            e = (x < mid_point ? lim_b : lim_a) - x;
            d = M_GOLDEN_RATIO * e;
        }


        if (std::abs(d) >= tolerance)
            u = d;
        else if (d > 0)
            u = tolerance;
        else
            u = -tolerance;
        u += x;
        fu = f(u);


        if (fu <= fx) {
            if (u < x)
                lim_b = x;
            else
                lim_a = x;
            v = w;
            fv = fw;
            w = x;
            fw = fx;
            x = u;
            fx = fu;
        } else {
            if (u < x)
                lim_a = u;
            else
                lim_b = u;
            if (fu <= fw || x == w) {
                v = w;
                fv = fw;
                w = u;
                fw = fu;
            } else if (fu <= fv || v == x || v == w) {
                v = u;
                fv = fu;
            }
        }

        iters++;
    } while (std::abs(x - mid_point) > (tolerance - (lim_b - lim_a) / 2.f));

    std::cout << " (iters: " << iters << ") ";

    return x;
}


void test1() {

    std::function<double(double)> f1 = [](double x) {
        return (x - 2) * (x - 2);
    };

    std::cout << "Test 1.... ";

    double minima = get_minima(f1, -1, 5);

    std::cout << minima << "...";

    assert(std::abs(minima - 2) < EPSILON);
    std::cout << "passed\n";
}


void test2() {


    std::function<double(double)> func = [](double x) {
        return -std::pow(x, 1.f / x);
    };

    std::cout << "Test 2.... ";

    double minima = get_minima(func, -2, 5);

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
    std::cout.precision(18);

    std::cout << "Computations performed with machine epsilon: " << EPSILON
              << "\n";

    test1();
    test2();
    test3();

    return 0;
}
