










namespace math {


std::array<std::complex<long double>, 2> quadraticEquation(long double a,
                                                           long double b,
                                                           long double c) {
    if (a == 0) {
        throw std::invalid_argument("quadratic coefficient cannot be 0");
    }

    long double discriminant = b * b - 4 * a * c;
    std::array<std::complex<long double>, 2> solutions{0, 0};

    if (discriminant == 0) {
        solutions[0] = -b * 0.5 / a;
        solutions[1] = -b * 0.5 / a;
        return solutions;
    }
    




    if (discriminant > 0) {


        solutions[0] = std::complex<long double>{
            (-b - std::sqrt(discriminant)) * 0.5 / a, 0};
        solutions[1] = std::complex<long double>{
            (-b + std::sqrt(discriminant)) * 0.5 / a, 0};
        return solutions;
    }


    solutions[0] = std::complex<long double>{
        -b * 0.5 / a, -std::sqrt(-discriminant) * 0.5 / a};
    solutions[1] = std::complex<long double>{
        -b * 0.5 / a, std::sqrt(-discriminant) * 0.5 / a};

    return solutions;
}

}


void assertArray(std::array<std::complex<long double>, 2> input,
                 std::array<std::complex<long double>, 2> expected,
                 size_t precision = 10) {
    long double exponent = std::pow(10, precision);
    input[0].real(std::round(input[0].real() * exponent));
    input[1].real(std::round(input[1].real() * exponent));
    input[0].imag(std::round(input[0].imag() * exponent));
    input[1].imag(std::round(input[1].imag() * exponent));

    expected[0].real(std::round(expected[0].real() * exponent));
    expected[1].real(std::round(expected[1].real() * exponent));
    expected[0].imag(std::round(expected[0].imag() * exponent));
    expected[1].imag(std::round(expected[1].imag() * exponent));

    assert(input == expected);
}


static void test() {

    std::cout << "Input: \n"
                 "a=1 \n"
                 "b=-2 \n"
                 "c=1 \n"
                 "Expected output: \n"
                 "(1, 0), (1, 0)\n\n";
    std::array<std::complex<long double>, 2> equalCase{
        std::complex<long double>{1, 0}, std::complex<long double>{1, 0}};
    assert(math::quadraticEquation(1, -2, 1) == equalCase);


    std::cout << "Input: \n"
                 "a=1 \n"
                 "b=4 \n"
                 "c=5 \n"
                 "Expected output: \n"
                 "(-2, -1), (-2, 1)\n\n";
    std::array<std::complex<long double>, 2> complexCase{
        std::complex<long double>{-2, -1}, std::complex<long double>{-2, 1}};
    assert(math::quadraticEquation(1, 4, 5) == complexCase);


    std::cout << "Input: \n"
                 "a=1 \n"
                 "b=5 \n"
                 "c=1 \n"
                 "Expected output: \n"
                 "(-4.7912878475, 0), (-0.2087121525, 0)\n\n";
    std::array<std::complex<long double>, 2> floatCase{
        std::complex<long double>{-4.7912878475, 0},
        std::complex<long double>{-0.2087121525, 0}};
    assertArray(math::quadraticEquation(1, 5, 1), floatCase);


    std::cout << "Input: \n"
                 "a=1 \n"
                 "b=1 \n"
                 "c=1 \n"
                 "Expected output: \n"
                 "(-0.5, -0.8660254038), (-0.5, 0.8660254038)\n\n";
    std::array<std::complex<long double>, 2> ifloatCase{
        std::complex<long double>{-0.5, -0.8660254038},
        std::complex<long double>{-0.5, 0.8660254038}};
    assertArray(math::quadraticEquation(1, 1, 1), ifloatCase);

    std::cout << "Exception test: \n"
                 "Input: \n"
                 "a=0 \n"
                 "b=0 \n"
                 "c=0\n"
                 "Expected output: Exception thrown \n";
    try {
        math::quadraticEquation(0, 0, 0);
    } catch (std::invalid_argument& e) {
        std::cout << "Exception thrown successfully \n";
    }
}


int main() {
    test();
    return 0;
}
