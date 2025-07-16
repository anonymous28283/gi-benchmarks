

















double _random(double a, double b) {
    return ((b - a) * (std::rand() % 100) / 100.f) + a;
}


int save_2d_data(const char *fname,
                 const std::vector<std::valarray<double>> &X) {
    size_t num_points = X.size();
    size_t num_features = X[0].size();

    std::ofstream fp;
    fp.open(fname);
    if (!fp.is_open()) {

        std::cerr << "Error opening file " << fname << ": "
                  << std::strerror(errno) << "\n";
        return -1;
    }


    for (int i = 0; i < num_points; i++) {

        for (int j = 0; j < num_features; j++) {
            fp << X[i][j];
            if (j < num_features - 1) {
                fp << ",";
            }
        }
        if (i < num_points - 1) {
            fp << "\n";
        }
    }

    fp.close();
    return 0;
}


void get_min_2d(const std::vector<std::valarray<double>> &X, double *val,
                int *x_idx, int *y_idx) {
    val[0] = INFINITY;
    size_t N = X.size();

    for (int i = 0; i < N; i++) {
        auto result = std::min_element(std::begin(X[i]), std::end(X[i]));
        double d_min = *result;
        std::ptrdiff_t j = std::distance(std::begin(X[i]), result);

        if (d_min < val[0]) {

            x_idx[0] = i;
            y_idx[0] = j;
            val[0] = d_min;
        }
    }
}


namespace machine_learning {

constexpr double MIN_DISTANCE = 1e-4;


int save_u_matrix(const char *fname,
                  const std::vector<std::vector<std::valarray<double>>> &W) {
    std::ofstream fp(fname);
    if (!fp) {
        std::cerr << "File error (" << fname << "): " << std::strerror(errno)
                  << std::endl;
        return -1;
    }


    unsigned int R = 1;

    for (int i = 0; i < W.size(); i++) {
        for (int j = 0; j < W[0].size(); j++) {
            double distance = 0.f;

            int from_x = std::max<int>(0, i - R);
            int to_x = std::min<int>(W.size(), i + R + 1);
            int from_y = std::max<int>(0, j - R);
            int to_y = std::min<int>(W[0].size(), j + R + 1);
            int l = 0, m = 0;



            for (l = from_x; l < to_x; l++) {
                for (m = from_y; m < to_y; m++) {
                    auto d = W[i][j] - W[l][m];
                    double d2 = std::pow(d, 2).sum();
                    distance += std::sqrt(d2);

                }
            }

            distance /= R * R;
            fp << distance;
            if (j < W[0].size() - 1) {
                fp << ',';
            }
        }
        if (i < W.size() - 1) {
            fp << '\n';
        }
    }

    fp.close();
    return 0;
}


double update_weights(const std::valarray<double> &X,
                      std::vector<std::vector<std::valarray<double>>> *W,
                      std::vector<std::valarray<double>> *D, double alpha,
                      int R) {
    int x = 0, y = 0;
    int num_out_x = static_cast<int>(W->size());
    int num_out_y = static_cast<int>(W[0][0].size());


    double d_min = 0.f;





    for (x = 0; x < num_out_x; x++) {
        for (y = 0; y < num_out_y; y++) {
            (*D)[x][y] = 0.f;


            auto d = ((*W)[x][y] - X);
            (*D)[x][y] = (d * d).sum();
            (*D)[x][y] = std::sqrt((*D)[x][y]);
        }
    }



    int d_min_x = 0, d_min_y = 0;
    get_min_2d(*D, &d_min, &d_min_x, &d_min_y);


    int from_x = std::max(0, d_min_x - R);
    int to_x = std::min(num_out_x, d_min_x + R + 1);
    int from_y = std::max(0, d_min_y - R);
    int to_y = std::min(num_out_y, d_min_y + R + 1);






    for (x = from_x; x < to_x; x++) {
        for (y = from_y; y < to_y; y++) {





            double d2 =
                (d_min_x - x) * (d_min_x - x) + (d_min_y - y) * (d_min_y - y);
            double scale_factor = std::exp(-d2 / (2.f * alpha * alpha));

            (*W)[x][y] += (X - (*W)[x][y]) * alpha * scale_factor;
        }
    }
    return d_min;
}


void kohonen_som(const std::vector<std::valarray<double>> &X,
                 std::vector<std::vector<std::valarray<double>>> *W,
                 double alpha_min) {
    size_t num_samples = X.size();

    size_t num_out = W->size();
    size_t R = num_out >> 2, iter = 0;
    double alpha = 1.f;

    std::vector<std::valarray<double>> D(num_out);
    for (int i = 0; i < num_out; i++) D[i] = std::valarray<double>(num_out);

    double dmin = 1.f;
    double past_dmin = 1.f;
    double dmin_ratio = 1.f;


    for (; alpha > 0 && dmin_ratio > 1e-5; alpha -= 1e-4, iter++) {

        for (int sample = 0; sample < num_samples; sample++) {

            dmin += update_weights(X[sample], W, &D, alpha, R);
        }


        if (iter % 300 == 0 && R > 1) {
            R--;
        }

        dmin /= num_samples;


        dmin_ratio = (past_dmin - dmin) / past_dmin;
        if (dmin_ratio < 0) {
            dmin_ratio = 1.f;
        }
        past_dmin = dmin;

        std::cout << "iter: " << iter << "\t alpha: " << alpha << "\t R: " << R
                  << "\t d_min: " << dmin_ratio << "\r";
    }

    std::cout << "\n";
}

}

using machine_learning::kohonen_som;
using machine_learning::save_u_matrix;




void test_2d_classes(std::vector<std::valarray<double>> *data) {
    const int N = data->size();
    const double R = 0.3;
    int i = 0;
    const int num_classes = 4;
    std::array<std::array<double, 2>, num_classes> centres = {

        std::array<double, 2>({.5, .5}),
        std::array<double, 2>({.5, -.5}),
        std::array<double, 2>({-.5, .5}),
        std::array<double, 2>({-.5, -.5})
    };




    for (i = 0; i < N; i++) {

        int cls = std::rand() % num_classes;


        data[0][i][0] = _random(centres[cls][0] - R, centres[cls][0] + R);
        data[0][i][1] = _random(centres[cls][1] - R, centres[cls][1] + R);


    }
}


void test1() {
    int j = 0, N = 300;
    int features = 2;
    int num_out = 30;
    std::vector<std::valarray<double>> X(N);
    std::vector<std::vector<std::valarray<double>>> W(num_out);
    for (int i = 0; i < std::max(num_out, N); i++) {

        if (i < N) {
            X[i] = std::valarray<double>(features);
        }
        if (i < num_out) {
            W[i] = std::vector<std::valarray<double>>(num_out);
            for (int k = 0; k < num_out; k++) {
                W[i][k] = std::valarray<double>(features);



                for (j = 0; j < features; j++) {

                    W[i][k][j] = _random(-10, 10);
                }
            }
        }
    }

    test_2d_classes(&X);
    save_2d_data("test1.csv", X);
    save_u_matrix("w11.csv", W);
    kohonen_som(X, &W, 1e-4);
    save_u_matrix("w12.csv", W);
}


void test_3d_classes1(std::vector<std::valarray<double>> *data) {
    const size_t N = data->size();
    const double R = 0.3;
    int i = 0;
    const int num_classes = 4;
    const std::array<std::array<double, 3>, num_classes> centres = {

        std::array<double, 3>({.5, .5, .5}),
        std::array<double, 3>({.5, -.5, -.5}),
        std::array<double, 3>({-.5, .5, .5}),
        std::array<double, 3>({-.5, -.5 - .5})
    };




    for (i = 0; i < N; i++) {

        int cls = std::rand() % num_classes;


        data[0][i][0] = _random(centres[cls][0] - R, centres[cls][0] + R);
        data[0][i][1] = _random(centres[cls][1] - R, centres[cls][1] + R);
        data[0][i][2] = _random(centres[cls][2] - R, centres[cls][2] + R);


    }
}


void test2() {
    int j = 0, N = 300;
    int features = 3;
    int num_out = 30;
    std::vector<std::valarray<double>> X(N);
    std::vector<std::vector<std::valarray<double>>> W(num_out);
    for (int i = 0; i < std::max(num_out, N); i++) {

        if (i < N) {
            X[i] = std::valarray<double>(features);
        }
        if (i < num_out) {
            W[i] = std::vector<std::valarray<double>>(num_out);
            for (int k = 0; k < num_out; k++) {
                W[i][k] = std::valarray<double>(features);



                for (j = 0; j < features; j++) {

                    W[i][k][j] = _random(-10, 10);
                }
            }
        }
    }

    test_3d_classes1(&X);
    save_2d_data("test2.csv", X);
    save_u_matrix("w21.csv", W);
    kohonen_som(X, &W, 1e-4);
    save_u_matrix("w22.csv", W);
}


void test_3d_classes2(std::vector<std::valarray<double>> *data) {
    const size_t N = data->size();
    const double R = 0.2;
    int i = 0;
    const int num_classes = 8;
    const std::array<std::array<double, 3>, num_classes> centres = {

        std::array<double, 3>({.5, .5, .5}),
        std::array<double, 3>({.5, .5, -.5}),
        std::array<double, 3>({.5, -.5, .5}),
        std::array<double, 3>({.5, -.5, -.5}),
        std::array<double, 3>({-.5, .5, .5}),
        std::array<double, 3>({-.5, .5, -.5}),
        std::array<double, 3>({-.5, -.5, .5}),
        std::array<double, 3>({-.5, -.5, -.5})
    };




    for (i = 0; i < N; i++) {

        int cls = std::rand() % num_classes;


        data[0][i][0] = _random(centres[cls][0] - R, centres[cls][0] + R);
        data[0][i][1] = _random(centres[cls][1] - R, centres[cls][1] + R);
        data[0][i][2] = _random(centres[cls][2] - R, centres[cls][2] + R);


    }
}


void test3() {
    int j = 0, N = 500;
    int features = 3;
    int num_out = 30;
    std::vector<std::valarray<double>> X(N);
    std::vector<std::vector<std::valarray<double>>> W(num_out);
    for (int i = 0; i < std::max(num_out, N); i++) {

        if (i < N) {
            X[i] = std::valarray<double>(features);
        }
        if (i < num_out) {
            W[i] = std::vector<std::valarray<double>>(num_out);
            for (int k = 0; k < num_out; k++) {
                W[i][k] = std::valarray<double>(features);



                for (j = 0; j < features; j++) {

                    W[i][k][j] = _random(-10, 10);
                }
            }
        }
    }

    test_3d_classes2(&X);
    save_2d_data("test3.csv", X);
    save_u_matrix("w31.csv", W);
    kohonen_som(X, &W, 1e-4);
    save_u_matrix("w32.csv", W);
}


double get_clock_diff(clock_t start_t, clock_t end_t) {
    return static_cast<double>(end_t - start_t) / CLOCKS_PER_SEC;
}


int main(int argc, char **argv) {

    std::cout << "Using OpenMP based parallelization\n";

    std::cout << "NOT using OpenMP based parallelization\n";


    std::srand(std::time(nullptr));

    std::clock_t start_clk = std::clock();
    test1();
    auto end_clk = std::clock();
    std::cout << "Test 1 completed in " << get_clock_diff(start_clk, end_clk)
              << " sec\n";

    start_clk = std::clock();
    test2();
    end_clk = std::clock();
    std::cout << "Test 2 completed in " << get_clock_diff(start_clk, end_clk)
              << " sec\n";

    start_clk = std::clock();
    test3();
    end_clk = std::clock();
    std::cout << "Test 3 completed in " << get_clock_diff(start_clk, end_clk)
              << " sec\n";

    std::cout
        << "(Note: Calculated times include: creating test sets, training "
           "model and writing files to disk.)\n\n";
    return 0;
}
