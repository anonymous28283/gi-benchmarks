







uint64_t finding_number_of_digits_in_a_number(uint64_t n) {
    uint64_t count = 0;




    while (n != 0) {

        n /= 10;

        ++count;
    }

    return count;
}


double finding_number_of_digits_in_a_number_using_log(double n) {

    if (n == 0) {
        return 0;
    }


    if (n < 0) {
        n = -n;
    }

    double count = floor(log10(n) + 1);

    return count;
}


static void first_test() {
    assert(finding_number_of_digits_in_a_number(5492) == 4);
    assert(finding_number_of_digits_in_a_number(-0) == 0);
    assert(finding_number_of_digits_in_a_number(10000) == 5);
    assert(finding_number_of_digits_in_a_number(9) == 1);
    assert(finding_number_of_digits_in_a_number(100000) == 6);
    assert(finding_number_of_digits_in_a_number(13) == 2);
    assert(finding_number_of_digits_in_a_number(564) == 3);
}

static void second_test() {
    assert(finding_number_of_digits_in_a_number_using_log(5492) == 4);
    assert(finding_number_of_digits_in_a_number_using_log(-0) == 0);
    assert(finding_number_of_digits_in_a_number_using_log(10000) == 5);
    assert(finding_number_of_digits_in_a_number_using_log(9) == 1);
    assert(finding_number_of_digits_in_a_number_using_log(100000) == 6);
    assert(finding_number_of_digits_in_a_number_using_log(13) == 2);
    assert(finding_number_of_digits_in_a_number_using_log(564) == 3);
}

int main() {

    first_test();
    second_test();
    std::cout << "All tests have successfully passed!\n";
    return 0;
}
