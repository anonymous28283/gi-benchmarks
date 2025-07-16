






namespace math {

namespace ncr_modulo_p {


namespace utils {

int64_t gcdExtended(const int64_t& a, const int64_t& b, int64_t& x,
                    int64_t& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    int64_t x1 = 0, y1 = 0;
    const int64_t gcd = gcdExtended(b % a, a, x1, y1);

    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}


int64_t modInverse(const int64_t& a, const int64_t& m) {
    int64_t x = 0, y = 0;
    const int64_t g = gcdExtended(a, m, x, y);
    if (g != 1) {
        return -1;
    } else {
        return ((x + m) % m);
    }
}
}

class NCRModuloP {
 private:
    const int64_t p = 0;
    const std::vector<int64_t>
        fac;


    static std::vector<int64_t> computeFactorialsMod(const int64_t& max_arg_val,
                                                     const int64_t& mod) {
        auto res = std::vector<int64_t>(max_arg_val + 1);
        res[0] = 1;
        for (int64_t i = 1; i <= max_arg_val; i++) {
            res[i] = (res[i - 1] * i) % mod;
        }
        return res;
    }

 public:

    NCRModuloP(const int64_t& size, const int64_t& p)
        : p(p), fac(computeFactorialsMod(size, p)) {}


    int64_t ncr(const int64_t& n, const int64_t& r) const {

        if (r > n) {
            return 0;
        }
        if (r == 1) {
            return n % p;
        }
        if (r == 0 || r == n) {
            return 1;
        }

        const auto denominator = (fac[r] * fac[n - r]) % p;
        const auto denominator_inv = utils::modInverse(denominator, p);
        if (denominator_inv < 0) {
            return -1;
        }
        return (fac[n] * denominator_inv) % p;
    }
};
}
}


static void tests() {
    struct TestCase {
        const int64_t size;
        const int64_t p;
        const int64_t n;
        const int64_t r;
        const int64_t expected;

        TestCase(const int64_t size, const int64_t p, const int64_t n,
                 const int64_t r, const int64_t expected)
            : size(size), p(p), n(n), r(r), expected(expected) {}
    };
    const std::vector<TestCase> test_cases = {
        TestCase(60000, 1000000007, 52323, 26161, 224944353),
        TestCase(20, 5, 6, 2, 30 % 5),
        TestCase(100, 29, 7, 3, 35 % 29),
        TestCase(1000, 13, 10, 3, 120 % 13),
        TestCase(20, 17, 1, 10, 0),
        TestCase(45, 19, 23, 1, 23 % 19),
        TestCase(45, 19, 23, 0, 1),
        TestCase(45, 19, 23, 23, 1),
        TestCase(20, 9, 10, 2, -1)};
    for (const auto& tc : test_cases) {
        assert(math::ncr_modulo_p::NCRModuloP(tc.size, tc.p).ncr(tc.n, tc.r) ==
               tc.expected);
    }

    std::cout << "\n\nAll tests have successfully passed!\n";
}


void example() {
    const int64_t size = 1e6 + 1;
    const int64_t p = 1e9 + 7;



    const auto ncrObj = math::ncr_modulo_p::NCRModuloP(size, p);



    for (int i = 0; i <= 7; i++) {
        std::cout << 6 << "C" << i << " mod " << p << " = " << ncrObj.ncr(6, i)
                  << "\n";
    }
}

int main() {
    tests();
    example();
    return 0;
}
