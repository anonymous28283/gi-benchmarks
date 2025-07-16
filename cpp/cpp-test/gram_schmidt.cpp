









namespace numerical_methods {

namespace gram_schmidt {

double dot_product(const std::array<double, 10>& x,
                   const std::array<double, 10>& y, const int& c) {
    double sum = 0;
    for (int i = 0; i < c; ++i) {
        sum += x[i] * y[i];
    }
    return sum;
}


double projection(const std::array<double, 10>& x,
                  const std::array<double, 10>& y, const int& c) {
    double dot =
        dot_product(x, y, c);
    double anorm =
        dot_product(y, y, c);
    double factor =
        dot /
        anorm;

    return factor;
}


void display(const int& r, const int& c,
             const std::array<std::array<double, 10>, 20>& B) {
    for (int i = 0; i < r; ++i) {
        std::cout << "Vector " << i + 1 << ": ";
        for (int j = 0; j < c; ++j) {
            std::cout << B[i][j] << " ";
        }
        std::cout << '\n';
    }
}


void gram_schmidt(int r, const int& c,
                  const std::array<std::array<double, 10>, 20>& A,
                  std::array<std::array<double, 10>, 20> B) {
    if (c < r) {
        std::cout << "Dimension of vector is less than number of vector, hence "
                     "\n first "
                  << c << " vectors are orthogonalised\n";
        r = c;
    }

    int k = 1;

    while (k <= r) {
        if (k == 1) {
            for (int j = 0; j < c; j++)
                B[0][j] = A[0][j];
        }

        else {
            std::array<double, 10>
                all_projection{};
            for (int i = 0; i < c; ++i) {
                all_projection[i] = 0;
            }

            int l = 1;
            while (l < k) {
                std::array<double, 10>
                    temp{};
                double factor = NAN;

                factor = projection(A[k - 1], B[l - 1], c);
                for (int i = 0; i < c; ++i) {
                    temp[i] = B[l - 1][i] * factor;
                }
                for (int j = 0; j < c; ++j) {
                    all_projection[j] =
                        all_projection[j] +
                        temp[j];

                }
                l++;
            }
            for (int i = 0; i < c; ++i) {
                B[k - 1][i] =
                    A[k - 1][i] -
                    all_projection[i];

            }
        }
        k++;
    }
    display(r, c, B);
}
}
}

static void test() {
    std::array<std::array<double, 10>, 20> a1 = {
        {{1, 0, 1, 0}, {1, 1, 1, 1}, {0, 1, 2, 1}}};
    std::array<std::array<double, 10>, 20> b1 = {{0}};
    double dot1 = 0;
    numerical_methods::gram_schmidt::gram_schmidt(3, 4, a1, b1);
    int flag = 1;
    for (int i = 0; i < 2; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            dot1 = fabs(
                numerical_methods::gram_schmidt::dot_product(b1[i], b1[j], 4));
            if (dot1 > 0.1) {
                flag = 0;
                break;
            }
        }
    }
    if (flag == 0)
        std::cout << "Vectors are linearly dependent\n";
    assert(flag == 1);
    std::cout << "Passed Test Case 1\n ";

    std::array<std::array<double, 10>, 20> a2 = {{{3, 1}, {2, 2}}};
    std::array<std::array<double, 10>, 20> b2 = {{0}};
    double dot2 = 0;
    numerical_methods::gram_schmidt::gram_schmidt(2, 2, a2, b2);
    flag = 1;
    for (int i = 0; i < 1; ++i) {
        for (int j = i + 1; j < 2; ++j) {
            dot2 = fabs(
                numerical_methods::gram_schmidt::dot_product(b2[i], b2[j], 2));
            if (dot2 > 0.1) {
                flag = 0;
                break;
            }
        }
    }
    if (flag == 0)
        std::cout << "Vectors are linearly dependent\n";
    assert(flag == 1);
    std::cout << "Passed Test Case 2\n";

    std::array<std::array<double, 10>, 20> a3 = {{{1, 2, 2}, {-4, 3, 2}}};
    std::array<std::array<double, 10>, 20> b3 = {{0}};
    double dot3 = 0;
    numerical_methods::gram_schmidt::gram_schmidt(2, 3, a3, b3);
    flag = 1;
    for (int i = 0; i < 1; ++i) {
        for (int j = i + 1; j < 2; ++j) {
            dot3 = fabs(
                numerical_methods::gram_schmidt::dot_product(b3[i], b3[j], 3));
            if (dot3 > 0.1) {
                flag = 0;
                break;
            }
        }
    }
    if (flag == 0)
        std::cout << "Vectors are linearly dependent\n";
    assert(flag == 1);
    std::cout << "Passed Test Case 3\n";
}


int main() {
    int r = 0, c = 0;
    test();
    std::cout << "Enter the dimension of your vectors\n";
    std::cin >> c;
    std::cout << "Enter the number of vectors you will enter\n";
    std::cin >> r;

    std::array<std::array<double, 10>, 20>
        A{};
    std::array<std::array<double, 10>, 20> B = {
        {0}};

    for (int i = 0; i < r; ++i) {
        std::cout << "Enter vector " << i + 1
                  << '\n';
        for (int j = 0; j < c; ++j) {
            std::cout << "Value " << j + 1 << "th of vector: ";
            std::cin >> A[i][j];
        }
        std::cout << '\n';
    }

    numerical_methods::gram_schmidt::gram_schmidt(r, c, A, B);

    double dot = 0;
    int flag = 1;
    for (int i = 0; i < r - 1; ++i) {
        for (int j = i + 1; j < r; ++j) {
            dot = fabs(
                numerical_methods::gram_schmidt::dot_product(B[i], B[j], c));
            if (dot > 0.1)

            {
                flag = 0;
                break;
            }
        }
    }
    if (flag == 0)
        std::cout << "Vectors are linearly dependent\n";
    return 0;
}
