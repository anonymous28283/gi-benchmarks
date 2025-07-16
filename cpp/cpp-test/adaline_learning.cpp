












constexpr int MAX_ITER = 500;


namespace machine_learning {
class adaline {
 public:

    explicit adaline(int num_features, const double eta = 0.01f,
                     const double accuracy = 1e-5)
        : eta(eta), accuracy(accuracy) {
        if (eta <= 0) {
            std::cerr << "learning rate should be positive and nonzero"
                      << std::endl;
            std::exit(EXIT_FAILURE);
        }

        weights = std::vector<double>(
            num_features +
            1);


        for (double &weight : weights) weight = 1.f;

    }


    friend std::ostream &operator<<(std::ostream &out, const adaline &ada) {
        out << "<";
        for (int i = 0; i < ada.weights.size(); i++) {
            out << ada.weights[i];
            if (i < ada.weights.size() - 1) {
                out << ", ";
            }
        }
        out << ">";
        return out;
    }


    int predict(const std::vector<double> &x, double *out = nullptr) {
        if (!check_size_match(x)) {
            return 0;
        }

        double y = weights.back();


        y = std::inner_product(x.begin(), x.end(), weights.begin(), y);

        if (out != nullptr) {
            *out = y;
        }

        return activation(y);
    }


    double fit(const std::vector<double> &x, const int &y) {
        if (!check_size_match(x)) {
            return 0;
        }


        int p = predict(x);
        int prediction_error = y - p;
        double correction_factor = eta * prediction_error;


        for (int i = 0; i < x.size(); i++) {
            weights[i] += correction_factor * x[i];
        }
        weights[x.size()] += correction_factor;

        return correction_factor;
    }


    template <size_t N>
    void fit(std::array<std::vector<double>, N> const &X,
             std::array<int, N> const &Y) {
        double avg_pred_error = 1.f;

        int iter = 0;
        for (iter = 0; (iter < MAX_ITER) && (avg_pred_error > accuracy);
             iter++) {
            avg_pred_error = 0.f;


            for (int i = 0; i < N; i++) {
                double err = fit(X[i], Y[i]);
                avg_pred_error += std::abs(err);
            }
            avg_pred_error /= N;



            std::cout << "\tIter " << iter << ": Training weights: " << *this
                      << "\tAvg error: " << avg_pred_error << std::endl;
        }

        if (iter < MAX_ITER) {
            std::cout << "Converged after " << iter << " iterations."
                      << std::endl;
        } else {
            std::cout << "Did not converge after " << iter << " iterations."
                      << std::endl;
        }
    }


    int activation(double x) { return x > 0 ? 1 : -1; }

 private:

    bool check_size_match(const std::vector<double> &x) {
        if (x.size() != (weights.size() - 1)) {
            std::cerr << __func__ << ": "
                      << "Number of features in x does not match the feature "
                         "dimension in model!"
                      << std::endl;
            return false;
        }
        return true;
    }

    const double eta;
    const double accuracy;
    std::vector<double> weights;
};

}

using machine_learning::adaline;




void test1(double eta = 0.01) {
    adaline ada(2, eta);

    const int N = 10;

    std::array<std::vector<double>, N> X = {
        std::vector<double>({0, 1}),   std::vector<double>({1, -2}),
        std::vector<double>({2, 3}),   std::vector<double>({3, -1}),
        std::vector<double>({4, 1}),   std::vector<double>({6, -5}),
        std::vector<double>({-7, -3}), std::vector<double>({-8, 5}),
        std::vector<double>({-9, 2}),  std::vector<double>({-10, -15})};
    std::array<int, N> y = {1,  -1, 1, -1, -1,
                            -1, 1,  1, 1,  -1};

    std::cout << "------- Test 1 -------" << std::endl;
    std::cout << "Model before fit: " << ada << std::endl;

    ada.fit<N>(X, y);
    std::cout << "Model after fit: " << ada << std::endl;

    int predict = ada.predict({5, -3});
    std::cout << "Predict for x=(5,-3): " << predict;
    assert(predict == -1);
    std::cout << " ...passed" << std::endl;

    predict = ada.predict({5, 8});
    std::cout << "Predict for x=(5,8): " << predict;
    assert(predict == 1);
    std::cout << " ...passed" << std::endl;
}


void test2(double eta = 0.01) {
    adaline ada(2, eta);

    const int N = 50;

    std::array<std::vector<double>, N> X;
    std::array<int, N> Y{};



    int range = 500;
    int range2 = range >> 1;
    for (int i = 0; i < N; i++) {
        double x0 = (static_cast<double>(std::rand() % range) - range2) / 100.f;
        double x1 = (static_cast<double>(std::rand() % range) - range2) / 100.f;
        X[i] = std::vector<double>({x0, x1});
        Y[i] = (x0 + 3. * x1) > -1 ? 1 : -1;
    }

    std::cout << "------- Test 2 -------" << std::endl;
    std::cout << "Model before fit: " << ada << std::endl;

    ada.fit(X, Y);
    std::cout << "Model after fit: " << ada << std::endl;

    int N_test_cases = 5;
    for (int i = 0; i < N_test_cases; i++) {
        double x0 = (static_cast<double>(std::rand() % range) - range2) / 100.f;
        double x1 = (static_cast<double>(std::rand() % range) - range2) / 100.f;

        int predict = ada.predict({x0, x1});

        std::cout << "Predict for x=(" << x0 << "," << x1 << "): " << predict;

        int expected_val = (x0 + 3. * x1) > -1 ? 1 : -1;
        assert(predict == expected_val);
        std::cout << " ...passed" << std::endl;
    }
}


void test3(double eta = 0.01) {
    adaline ada(6, eta);

    const int N = 100;

    std::array<std::vector<double>, N> X;
    std::array<int, N> Y{};



    int range = 200;
    int range2 = range >> 1;
    for (int i = 0; i < N; i++) {
        double x0 = (static_cast<double>(std::rand() % range) - range2) / 100.f;
        double x1 = (static_cast<double>(std::rand() % range) - range2) / 100.f;
        double x2 = (static_cast<double>(std::rand() % range) - range2) / 100.f;
        X[i] = std::vector<double>({x0, x1, x2, x0 * x0, x1 * x1, x2 * x2});
        Y[i] = ((x0 * x0) + (x1 * x1) + (x2 * x2)) <= 1.f ? 1 : -1;
    }

    std::cout << "------- Test 3 -------" << std::endl;
    std::cout << "Model before fit: " << ada << std::endl;

    ada.fit(X, Y);
    std::cout << "Model after fit: " << ada << std::endl;

    int N_test_cases = 5;
    for (int i = 0; i < N_test_cases; i++) {
        double x0 = (static_cast<double>(std::rand() % range) - range2) / 100.f;
        double x1 = (static_cast<double>(std::rand() % range) - range2) / 100.f;
        double x2 = (static_cast<double>(std::rand() % range) - range2) / 100.f;

        int predict = ada.predict({x0, x1, x2, x0 * x0, x1 * x1, x2 * x2});

        std::cout << "Predict for x=(" << x0 << "," << x1 << "," << x2
                  << "): " << predict;

        int expected_val = ((x0 * x0) + (x1 * x1) + (x2 * x2)) <= 1.f ? 1 : -1;
        assert(predict == expected_val);
        std::cout << " ...passed" << std::endl;
    }
}


int main(int argc, char **argv) {
    std::srand(std::time(nullptr));

    double eta = 0.1;
    if (argc == 2) {
        eta = strtof(argv[1], nullptr);
    }

    test1(eta);

    std::cout << "Press ENTER to continue..." << std::endl;
    std::cin.get();

    test2(eta);

    std::cout << "Press ENTER to continue..." << std::endl;
    std::cin.get();

    test3(eta);

    return 0;
}
