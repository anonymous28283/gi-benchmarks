







template <typename T>
std::ostream &operator<<(std::ostream &out,
                         std::vector<std::vector<T>> const &v) {
    const int width = 10;
    const char separator = ' ';

    for (size_t row = 0; row < v.size(); row++) {
        for (size_t col = 0; col < v[row].size(); col++) {
            out << std::left << std::setw(width) << std::setfill(separator)
                << v[row][col];
        }
        out << std::endl;
    }

    return out;
}


template <typename T>
std::ostream &operator<<(std::ostream &out, std::vector<T> const &v) {
    const int width = 15;
    const char separator = ' ';

    for (size_t row = 0; row < v.size(); row++) {
        out << std::left << std::setw(width) << std::setfill(separator)
            << v[row];
    }

    return out;
}


template <typename T>
inline bool is_square(std::vector<std::vector<T>> const &A) {

    size_t N = A.size();
    for (size_t i = 0; i < N; i++) {
        if (A[i].size() != N) {
            return false;
        }
    }
    return true;
}


template <typename T>
std::vector<std::vector<T>> operator*(std::vector<std::vector<T>> const &A,
                                      std::vector<std::vector<T>> const &B) {

    size_t N_A = A.size();

    size_t N_B = B[0].size();

    std::vector<std::vector<T>> result(N_A);

    if (A[0].size() != B.size()) {
        std::cerr << "Number of columns in A != Number of rows in B ("
                  << A[0].size() << ", " << B.size() << ")" << std::endl;
        return result;
    }

    for (size_t row = 0; row < N_A; row++) {
        std::vector<T> v(N_B);
        for (size_t col = 0; col < N_B; col++) {
            v[col] = static_cast<T>(0);
            for (size_t j = 0; j < B.size(); j++) {
                v[col] += A[row][j] * B[j][col];
            }
        }
        result[row] = v;
    }

    return result;
}


template <typename T>
std::vector<T> operator*(std::vector<std::vector<T>> const &A,
                         std::vector<T> const &B) {

    size_t N_A = A.size();

    std::vector<T> result(N_A);

    if (A[0].size() != B.size()) {
        std::cerr << "Number of columns in A != Number of rows in B ("
                  << A[0].size() << ", " << B.size() << ")" << std::endl;
        return result;
    }

    for (size_t row = 0; row < N_A; row++) {
        result[row] = static_cast<T>(0);
        for (size_t j = 0; j < B.size(); j++) result[row] += A[row][j] * B[j];
    }

    return result;
}


template <typename T>
std::vector<float> operator*(float const scalar, std::vector<T> const &A) {

    size_t N_A = A.size();

    std::vector<float> result(N_A);

    for (size_t row = 0; row < N_A; row++) {
        result[row] += A[row] * static_cast<float>(scalar);
    }

    return result;
}


template <typename T>
std::vector<float> operator*(std::vector<T> const &A, float const scalar) {

    size_t N_A = A.size();

    std::vector<float> result(N_A);

    for (size_t row = 0; row < N_A; row++) {
        result[row] = A[row] * static_cast<float>(scalar);
    }

    return result;
}


template <typename T>
std::vector<float> operator/(std::vector<T> const &A, float const scalar) {
    return (1.f / scalar) * A;
}


template <typename T>
std::vector<T> operator-(std::vector<T> const &A, std::vector<T> const &B) {

    size_t N = A.size();

    std::vector<T> result(N);

    if (B.size() != N) {
        std::cerr << "Vector dimensions shouldbe identical!" << std::endl;
        return A;
    }

    for (size_t row = 0; row < N; row++) result[row] = A[row] - B[row];

    return result;
}


template <typename T>
std::vector<T> operator+(std::vector<T> const &A, std::vector<T> const &B) {

    size_t N = A.size();

    std::vector<T> result(N);

    if (B.size() != N) {
        std::cerr << "Vector dimensions shouldbe identical!" << std::endl;
        return A;
    }

    for (size_t row = 0; row < N; row++) result[row] = A[row] + B[row];

    return result;
}


template <typename T>
std::vector<std::vector<float>> get_inverse(
    std::vector<std::vector<T>> const &A) {

    size_t N = A.size();

    std::vector<std::vector<float>> inverse(N);
    for (size_t row = 0; row < N; row++) {

        inverse[row] = std::vector<float>(N);
        for (size_t col = 0; col < N; col++) {
            inverse[row][col] = (row == col) ? 1.f : 0.f;
        }
    }

    if (!is_square(A)) {
        std::cerr << "A must be a square matrix!" << std::endl;
        return inverse;
    }


    std::vector<std::vector<float>> temp(N);
    for (size_t row = 0; row < N; row++) {
        std::vector<float> v(N);
        for (size_t col = 0; col < N; col++) {
            v[col] = static_cast<float>(A[row][col]);
        }
        temp[row] = v;
    }


    for (size_t row = 0; row < N; row++) {
        for (size_t row2 = row; row2 < N && temp[row][row] == 0; row2++) {

            temp[row] = temp[row] + temp[row2];
            inverse[row] = inverse[row] + inverse[row2];
        }

        for (size_t col2 = row; col2 < N && temp[row][row] == 0; col2++) {

            for (size_t row2 = 0; row2 < N; row2++) {
                temp[row2][row] = temp[row2][row] + temp[row2][col2];
                inverse[row2][row] = inverse[row2][row] + inverse[row2][col2];
            }
        }

        if (temp[row][row] == 0) {

            std::cerr << "Low-rank matrix, no inverse!" << std::endl;
            return inverse;
        }


        auto divisor = static_cast<float>(temp[row][row]);
        temp[row] = temp[row] / divisor;
        inverse[row] = inverse[row] / divisor;

        for (size_t row2 = 0; row2 < N; row2++) {
            if (row2 == row) {
                continue;
            }
            float factor = temp[row2][row];
            temp[row2] = temp[row2] - factor * temp[row];
            inverse[row2] = inverse[row2] - factor * inverse[row];
        }
    }

    return inverse;
}


template <typename T>
std::vector<std::vector<T>> get_transpose(
    std::vector<std::vector<T>> const &A) {
    std::vector<std::vector<T>> result(A[0].size());

    for (size_t row = 0; row < A[0].size(); row++) {
        std::vector<T> v(A.size());
        for (size_t col = 0; col < A.size(); col++) v[col] = A[col][row];

        result[row] = v;
    }
    return result;
}


template <typename T>
std::vector<float> fit_OLS_regressor(std::vector<std::vector<T>> const &X,
                                     std::vector<T> const &Y) {

    std::vector<std::vector<T>> X2 = X;
    for (size_t i = 0; i < X2.size(); i++) {

        X2[i].push_back(1);
    }

    std::vector<std::vector<T>> Xt = get_transpose(X2);

    std::vector<std::vector<T>> tmp = get_inverse(Xt * X2);

    std::vector<std::vector<float>> out = tmp * Xt;




    return out * Y;
}


template <typename T>
std::vector<float> predict_OLS_regressor(std::vector<std::vector<T>> const &X,
                                         std::vector<float> const &beta
) {
    std::vector<float> result(X.size());

    for (size_t rows = 0; rows < X.size(); rows++) {

        result[rows] = beta[X[0].size()];
        for (size_t cols = 0; cols < X[0].size(); cols++) {
            result[rows] += beta[cols] * X[rows][cols];
        }
    }

    return result;
}


void ols_test() {
    int F = 3, N = 5;


    std::cout << "Test 1 (quadratic function)....";

    std::vector<std::vector<float>> data1(
        {{-5, 25, -125}, {-1, 1, -1}, {0, 0, 0}, {1, 1, 1}, {6, 36, 216}});

    std::vector<float> Y1({20, -4, -5, -4, 31});

    std::vector<float> beta1 = fit_OLS_regressor(data1, Y1);

    std::vector<std::vector<float>> test_data1(
        {{-2, 4, -8}, {2, 4, 8}, {-10, 100, -1000}, {10, 100, 1000}});

    std::vector<float> expected1({-1, -1, 95, 95});

    std::vector<float> out1 = predict_OLS_regressor(test_data1, beta1);

    for (size_t rows = 0; rows < out1.size(); rows++) {
        assert(std::abs(out1[rows] - expected1[rows]) < 0.01);
    }
    std::cout << "passed\n";


    std::cout << "Test 2 (cubic function)....";

    std::vector<std::vector<float>> data2(
        {{-5, 25, -125}, {-1, 1, -1}, {0, 0, 0}, {1, 1, 1}, {6, 36, 216}});

    std::vector<float> Y2({-200, -100, -100, 98, 152});

    std::vector<float> beta2 = fit_OLS_regressor(data2, Y2);

    std::vector<std::vector<float>> test_data2(
        {{-2, 4, -8}, {2, 4, 8}, {-10, 100, -1000}, {10, 100, 1000}});

    std::vector<float> expected2({-104, -88, -1000, 1000});

    std::vector<float> out2 = predict_OLS_regressor(test_data2, beta2);

    for (size_t rows = 0; rows < out2.size(); rows++) {
        assert(std::abs(out2[rows] - expected2[rows]) < 0.01);
    }
    std::cout << "passed\n";

    std::cout << std::endl;

}


int main() {
    ols_test();

    size_t N = 0, F = 0;

    std::cout << "Enter number of features: ";

    std::cin >> F;
    std::cout << "Enter number of samples: ";

    std::cin >> N;

    std::vector<std::vector<float>> data(N);
    std::vector<float> Y(N);

    std::cout
        << "Enter training data. Per sample, provide features and one output."
        << std::endl;

    for (size_t rows = 0; rows < N; rows++) {
        std::vector<float> v(F);
        std::cout << "Sample# " << rows + 1 << ": ";
        for (size_t cols = 0; cols < F; cols++) {

            std::cin >> v[cols];
        }
        data[rows] = v;

        std::cin >> Y[rows];
    }

    std::vector<float> beta = fit_OLS_regressor(data, Y);
    std::cout << std::endl << std::endl << "beta:" << beta << std::endl;

    size_t T = 0;
    std::cout << "Enter number of test samples: ";

    std::cin >> T;
    std::vector<std::vector<float>> data2(T);


    for (size_t rows = 0; rows < T; rows++) {
        std::cout << "Sample# " << rows + 1 << ": ";
        std::vector<float> v(F);
        for (size_t cols = 0; cols < F; cols++) std::cin >> v[cols];
        data2[rows] = v;
    }

    std::vector<float> out = predict_OLS_regressor(data2, beta);
    for (size_t rows = 0; rows < T; rows++) std::cout << out[rows] << std::endl;

    return 0;
}
