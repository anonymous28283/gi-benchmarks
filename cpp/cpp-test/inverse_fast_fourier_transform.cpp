









namespace numerical_methods {

std::complex<double> *InverseFastFourierTransform(std::complex<double> *p,
                                                  uint8_t n) {
    if (n == 1) {
        return p;
    }

    double pi = 2 * asin(1.0);

    std::complex<double> om = std::complex<double>(
        cos(2 * pi / n), sin(2 * pi / n));

    om.real(om.real() / n);
    om.imag(om.imag() / n);

    auto *pe = new std::complex<double>[n / 2];

    auto *po = new std::complex<double>[n / 2];

    int k1 = 0, k2 = 0;
    for (int j = 0; j < n; j++) {
        if (j % 2 == 0) {
            pe[k1++] = p[j];

        } else {
            po[k2++] = p[j];
        }
    }

    std::complex<double> *ye =
        InverseFastFourierTransform(pe, n / 2);

    std::complex<double> *yo =
        InverseFastFourierTransform(po, n / 2);

    auto *y = new std::complex<double>[n];

    k1 = 0, k2 = 0;

    for (int i = 0; i < n / 2; i++) {
        y[i] =
            ye[k1] + pow(om, i) * yo[k2];
        y[i + n / 2] =
            ye[k1] - pow(om, i) * yo[k2];

        k1++;
        k2++;
    }

    if (n != 2) {
        delete[] pe;
        delete[] po;
    }

    delete[] ye;
    delete[] yo;
    return y;
}

}


static void test() {


    auto *t1 = new std::complex<double>[2];
    auto *t2 = new std::complex<double>[4];

    t1[0] = {3, 0};
    t1[1] = {-1, 0};
    t2[0] = {10, 0};
    t2[1] = {-2, -2};
    t2[2] = {-2, 0};
    t2[3] = {-2, 2};

    uint8_t n1 = 2;
    uint8_t n2 = 4;
    std::vector<std::complex<double>> r1 = {
        {1, 0}, {2, 0}};

    std::vector<std::complex<double>> r2 = {
        {1, 0}, {2, 0}, {3, 0}, {4, 0}};

    std::complex<double> *o1 =
        numerical_methods::InverseFastFourierTransform(t1, n1);

    std::complex<double> *o2 =
        numerical_methods::InverseFastFourierTransform(t2, n2);

    for (uint8_t i = 0; i < n1; i++) {
        assert((r1[i].real() - o1[i].real() < 0.000000000001) &&
               (r1[i].imag() - o1[i].imag() <
                0.000000000001));

    }

    for (uint8_t i = 0; i < n2; i++) {
        assert((r2[i].real() - o2[i].real() < 0.000000000001) &&
               (r2[i].imag() - o2[i].imag() <
                0.000000000001));

    }

    delete[] t1;
    delete[] t2;
    delete[] o1;
    delete[] o2;
    std::cout << "All tests have successfully passed!\n";
}



int main(int argc, char const *argv[]) {
    test();

    return 0;
}
