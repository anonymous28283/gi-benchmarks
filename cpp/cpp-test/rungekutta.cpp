





static double change(double x, double y) { return ((x - y) / 2.0); }


namespace numerical_methods {

namespace runge_kutta {

double rungeKutta(double init_x, const double &init_y, const double &x,
                  const double &h) {








    auto n = static_cast<uint64_t>((x - init_x) / h);

    std::vector<double> k(4, 0.0);



    double y = init_y;
    for (int i = 1; i <= n; ++i) {


        k[0] = h * change(init_x, y);
        k[1] = h * change(init_x + 0.5 * h, y + 0.5 * k[0]);
        k[2] = h * change(init_x + 0.5 * h, y + 0.5 * k[1]);
        k[3] = h * change(init_x + h, y + k[2]);



        y += (1.0 / 6.0) * (k[0] + 2 * k[1] + 2 * k[2] + k[3]);



        init_x += h;
    }

    return y;
}
}
}


static void test() {
    std::cout << "The Runge Kutta function will be tested on the basis of "
                 "precomputed values\n";

    std::cout << "Test 1...."
              << "\n";
    double valfirst = numerical_methods::runge_kutta::rungeKutta(
        2, 3, 4, 0.2);
    assert(valfirst == 3.10363932323749570);
    std::cout << "Passed Test 1\n";

    std::cout << "Test 2...."
              << "\n";
    double valsec = numerical_methods::runge_kutta::rungeKutta(
        1, 2, 5, 0.1);
    assert(valsec == 3.40600589380261409);
    std::cout << "Passed Test 2\n";

    std::cout << "Test 3...."
              << "\n";
    double valthird = numerical_methods::runge_kutta::rungeKutta(
        -1, 3, 4, 0.1);
    assert(valthird == 2.49251005860244268);
    std::cout << "Passed Test 3\n";
}


int main() {
    test();
    return 0;
}
