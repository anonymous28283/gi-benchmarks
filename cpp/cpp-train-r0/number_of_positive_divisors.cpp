





int number_of_positive_divisors(int n) {
    if (n < 0) {
        n = -n;
    }

    int number_of_divisors = 1;

    for (int i = 2; i * i <= n; i++) {








        int prime_exponent = 0;
        while (n % i == 0) {


            prime_exponent++;
            n /= i;
        }
        number_of_divisors *= prime_exponent + 1;
    }
    if (n > 1) {


        number_of_divisors *= 2;
    }

    return number_of_divisors;
}


void tests() {
    assert(number_of_positive_divisors(36) == 9);
    assert(number_of_positive_divisors(-36) == 9);
    assert(number_of_positive_divisors(1) == 1);
    assert(number_of_positive_divisors(2011) == 2);
    assert(number_of_positive_divisors(756) == 24);
}


int main() {
    tests();
    int n;
    std::cin >> n;
    if (n == 0) {
        std::cout << "All non-zero numbers are divisors of 0 !" << std::endl;
    } else {
        std::cout << "Number of positive divisors is : ";
        std::cout << number_of_positive_divisors(n) << std::endl;
    }
    return 0;
}
