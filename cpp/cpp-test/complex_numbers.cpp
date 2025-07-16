









class Complex {

    double re;

    double im;

 public:

    explicit Complex(double x = 0.f, double y = 0.f, bool is_polar = false) {
        if (!is_polar) {
            re = x;
            im = y;
            return;
        }

        re = x * std::cos(y);
        im = x * std::sin(y);
    }


    Complex(const Complex &other) : re(other.real()), im(other.imag()) {}


    double real() const { return this->re; }


    double imag() const { return this->im; }


    double abs() const {
        return std::sqrt(this->re * this->re + this->im * this->im);
    }


    double arg() const { return std::atan2(this->im, this->re); }


    Complex operator+(const Complex &other) {
        Complex result(this->re + other.re, this->im + other.im);
        return result;
    }


    Complex operator-(const Complex &other) {
        Complex result(this->re - other.re, this->im - other.im);
        return result;
    }


    Complex operator*(const Complex &other) {
        Complex result(this->re * other.re - this->im * other.im,
                       this->re * other.im + this->im * other.re);
        return result;
    }


    Complex operator~() const {
        Complex result(this->re, -(this->im));
        return result;
    }


    Complex operator/(const Complex &other) {
        Complex result = *this * ~other;
        double denominator =
            other.real() * other.real() + other.imag() * other.imag();
        if (denominator != 0) {
            result = Complex(result.real() / denominator,
                             result.imag() / denominator);
            return result;
        } else {
            throw std::invalid_argument("Undefined Value");
        }
    }


    const Complex &operator=(const Complex &other) {
        this->re = other.real();
        this->im = other.imag();
        return *this;
    }
};


bool operator==(const Complex &a, const Complex &b) {
    return a.real() == b.real() && a.imag() == b.imag();
}


std::ostream &operator<<(std::ostream &os, const Complex &num) {
    os << "(" << num.real();
    if (num.imag() < 0) {
        os << " - " << -num.imag();
    } else {
        os << " + " << num.imag();
    }
    os << "i)";
    return os;
}


double get_rand() { return (std::rand() % 100 - 50) / 100.f; }


void tests() {
    std::srand(std::time(nullptr));
    double x1 = get_rand(), y1 = get_rand(), x2 = get_rand(), y2 = get_rand();
    Complex num1(x1, y1), num2(x2, y2);
    std::complex<double> cnum1(x1, y1), cnum2(x2, y2);
    Complex result;
    std::complex<double> expected;

    result = num1 + num2;
    expected = cnum1 + cnum2;
    assert(((void)"1 + 1i + 1 + 1i is equal to 2 + 2i but the addition doesn't "
                  "add up \n",
            (result.real() == expected.real() &&
             result.imag() == expected.imag())));
    std::cout << "First test passes." << std::endl;

    result = num1 - num2;
    expected = cnum1 - cnum2;
    assert(((void)"1 + 1i - 1 - 1i is equal to 0 but the program says "
                  "otherwise. \n",
            (result.real() == expected.real() &&
             result.imag() == expected.imag())));
    std::cout << "Second test passes." << std::endl;

    result = num1 * num2;
    expected = cnum1 * cnum2;
    assert(((void)"(1 + 1i) * (1 + 1i) is equal to 2i but the program says "
                  "otherwise. \n",
            (result.real() == expected.real() &&
             result.imag() == expected.imag())));
    std::cout << "Third test passes." << std::endl;

    result = num1 / num2;
    expected = cnum1 / cnum2;
    assert(((void)"(1 + 1i) / (1 + 1i) is equal to 1 but the program says "
                  "otherwise.\n",
            (result.real() == expected.real() &&
             result.imag() == expected.imag())));
    std::cout << "Fourth test passes." << std::endl;

    result = ~num1;
    expected = std::conj(cnum1);
    assert(((void)"(1 + 1i) has a conjugate which is equal to (1 - 1i) but the "
                  "program says otherwise.\n",
            (result.real() == expected.real() &&
             result.imag() == expected.imag())));
    std::cout << "Fifth test passes.\n";

    assert(((void)"(1 + 1i) has argument PI / 4 but the program differs from "
                  "the std::complex result.\n",
            (num1.arg() == std::arg(cnum1))));
    std::cout << "Sixth test passes.\n";

    assert(((void)"(1 + 1i) has absolute value sqrt(2) but the program differs "
                  "from the std::complex result. \n",
            (num1.abs() == std::abs(cnum1))));
    std::cout << "Seventh test passes.\n";
}


int main() {
    tests();
    return 0;
}
