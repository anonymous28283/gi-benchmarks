







namespace divide_and_conquer {

namespace karatsuba_algorithm {

std::string add_strings(std::string first, std::string second) {
    std::string result;


    int64_t len1 = first.size();
    int64_t len2 = second.size();
    std::string zero = "0";
    if (len1 < len2) {
        for (int64_t i = 0; i < len2 - len1; i++) {
            zero += first;
            first = zero;
            zero = "0";
        }
    } else if (len1 > len2) {
        for (int64_t i = 0; i < len1 - len2; i++) {
            zero += second;
            second = zero;
            zero = "0";
        }
    }

    int64_t length = std::max(len1, len2);
    int64_t carry = 0;
    for (int64_t i = length - 1; i >= 0; i--) {
        int64_t firstBit = first.at(i) - '0';
        int64_t secondBit = second.at(i) - '0';

        int64_t sum = (char(firstBit ^ secondBit ^ carry)) + '0';
        result.insert(result.begin(), sum);

        carry = char((firstBit & secondBit) | (secondBit & carry) |
                (firstBit & carry));
    }

    if (carry) {
        result.insert(result.begin(), '1');
    }
    return result;
}


std::string safe_substr(const std::string &str, int64_t x1, int64_t x2, int64_t n) {
    int64_t len = str.size();

    if (len >= n) {
        return str.substr(x1, x2);
    }

    int64_t y1 = x1 - (n - len);
    int64_t y2 = (x1 + x2 - 1) - (n - len);

    if (y2 < 0) {
        return "0";
    } else if (y1 < 0) {
        return str.substr(0, y2 + 1);
    } else {
        return str.substr(y1, x2);
    }
}


int64_t karatsuba_algorithm(std::string str1, std::string str2) {
    int64_t len1 = str1.size();
    int64_t len2 = str2.size();
    int64_t n = std::max(len1, len2);

    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return (str1[0] - '0') * (str2[0] - '0');
    }

    int64_t fh = n / 2;
    int64_t sh = n - fh;

    std::string Xl = divide_and_conquer::karatsuba_algorithm::safe_substr(str1, 0, fh, n);
    std::string Xr = divide_and_conquer::karatsuba_algorithm::safe_substr(str1, fh, sh, n);

    std::string Yl = divide_and_conquer::karatsuba_algorithm::safe_substr(str2, 0, fh, n);
    std::string Yr = divide_and_conquer::karatsuba_algorithm::safe_substr(str2, fh, sh, n);


    int64_t product1 = karatsuba_algorithm(Xl, Yl);
    int64_t product2 = karatsuba_algorithm(Xr, Yr);
    int64_t product3 = karatsuba_algorithm(
        divide_and_conquer::karatsuba_algorithm::add_strings(Xl, Xr),
        divide_and_conquer::karatsuba_algorithm::add_strings(Yl, Yr));

    return product1 * (1 << (2 * sh)) +
           (product3 - product1 - product2) * (1 << sh) +
           product2;
}
}
}


static void test() {

    std::string s11 = "1";
    std::string s12 = "1010";
    std::cout << "1st test... ";
    assert(divide_and_conquer::karatsuba_algorithm::karatsuba_algorithm(
               s11, s12) == 10);
    std::cout << "passed" << std::endl;


    std::string s21 = "11";
    std::string s22 = "1010";
    std::cout << "2nd test... ";
    assert(divide_and_conquer::karatsuba_algorithm::karatsuba_algorithm(
               s21, s22) == 30);
    std::cout << "passed" << std::endl;


    std::string s31 = "110";
    std::string s32 = "1010";
    std::cout << "3rd test... ";
    assert(divide_and_conquer::karatsuba_algorithm::karatsuba_algorithm(
               s31, s32) == 60);
    std::cout << "passed" << std::endl;
}


int main() {
    test();
    return 0;
}
