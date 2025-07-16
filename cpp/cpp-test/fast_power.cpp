









template <typename T>
double fast_power_recursive(T a, T b) {

    if (b < 0)
        return 1.0 / fast_power_recursive(a, -b);

    if (b == 0)
        return 1;
    T bottom = fast_power_recursive(a, b >> 1);



    double result;
    if ((b & 1) == 0)
        result = bottom * bottom;
    else
        result = bottom * bottom * a;
    return result;
}


template <typename T>
double fast_power_linear(T a, T b) {

    if (b < 0)
        return 1.0 / fast_power_linear(a, -b);

    double result = 1;
    while (b) {
        if (b & 1)
            result = result * a;
        a = a * a;
        b = b >> 1;
    }
    return result;
}


int main() {
    std::srand(std::time(nullptr));
    std::ios_base::sync_with_stdio(false);

    std::cout << "Testing..." << std::endl;
    for (int i = 0; i < 20; i++) {
        int a = std::rand() % 20 - 10;
        int b = std::rand() % 20 - 10;
        std::cout << std::endl << "Calculating " << a << "^" << b << std::endl;
        assert(fast_power_recursive(a, b) == std::pow(a, b));
        assert(fast_power_linear(a, b) == std::pow(a, b));

        std::cout << "------ " << a << "^" << b << " = "
                  << fast_power_recursive(a, b) << std::endl;
    }

    int64_t a, b;
    std::cin >> a >> b;

    std::cout << a << "^" << b << " = " << fast_power_recursive(a, b)
              << std::endl;

    std::cout << a << "^" << b << " = " << fast_power_linear(a, b) << std::endl;

    return 0;
}
