







template <typename T>
std::vector<T> reverse_binary(T num) {
    std::vector<T> result;
    T temp = num;
    while (temp > 0) {
        result.push_back(temp % 2);
        temp = temp / 2;
    }
    return result;
}


template <typename T>
T modular_exponentiation(T base, const std::vector<T> &rev_binary_exponent,
                         T mod) {
    if (mod == 1)
        return 0;
    T b = 1;
    if (rev_binary_exponent.size() == 0)
        return b;
    T A = base;
    if (rev_binary_exponent[0] == 1)
        b = base;

    for (typename std::vector<T>::const_iterator it =
             rev_binary_exponent.cbegin() + 1;
         it != rev_binary_exponent.cend(); ++it) {
        A = A * A % mod;
        if (*it == 1)
            b = A * b % mod;
    }
    return b;
}


template <typename T>
bool miller_test(T d, T num) {

    std::random_device rd_seed;

    std::mt19937 gen(rd_seed());

    std::uniform_int_distribution<> distribution(2, num - 2);

    T random = distribution(gen);

    std::vector<T> power = reverse_binary(d);

    T x = modular_exponentiation(random, power, num);

    if (x == 1 || x == num - 1) {
        return true;
    }

    while (d != num - 1) {
        x = (x * x) % num;
        d *= 2;
        if (x == 1) {
            return false;
        }
        if (x == num - 1) {
            return true;
        }
    }
    return false;
}


template <typename T>
bool miller_rabin_primality_test(T num, T repeats) {
    if (num <= 4) {

        if (num == 2 || num == 3) {
            return true;
        } else {
            return false;
        }
    }

    if (num % 2 == 0) {
        return false;
    }

    T d = num - 1, r = 0;
    while (d % 2 == 0) {
        d = d / 2;
        r++;
    }

    for (T i = 0; i < repeats; ++i) {
        if (!miller_test(d, num)) {
            return false;
        }
    }
    return true;
}


void tests() {

    assert(((void)"2 is prime but function says otherwise.\n",
            miller_rabin_primality_test(2, 1) == true));
    std::cout << "First test passes." << std::endl;

    assert(((void)"5 should be prime but the function says otherwise.\n",
            miller_rabin_primality_test(5, 3) == true));
    std::cout << "Second test passes." << std::endl;

    assert(((void)"23 should be prime but the function says otherwise.\n",
            miller_rabin_primality_test(23, 3) == true));
    std::cout << "Third test passes." << std::endl;

    assert(((void)"16 is not a prime but the function says otherwise.\n",
            miller_rabin_primality_test(16, 3) == false));
    std::cout << "Fourth test passes." << std::endl;

    assert(((void)"27 is not a prime but the function says otherwise.\n",
            miller_rabin_primality_test(27, 3) == false));
    std::cout << "Fifth test passes." << std::endl;
}


int main() {
    tests();
    return 0;
}
