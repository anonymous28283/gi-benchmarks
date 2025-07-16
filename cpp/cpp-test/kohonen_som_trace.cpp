















double _random(double a, double b) {
    return ((b - a) * (std::rand() % 100) / 100.f) + a;
}


int save_nd_data(const char *fname,
                 const std::vector<std::valarray<double>> &X) {
    size_t num_points = X.size();
    size_t num_features = X[0].size();

    std::ofstream fp;
    fp.open(fname);
    if (!fp.is_open()) {

        std::cerr << "Error opening file " << fname << "\n";
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


namespace machine_learning {


void update_weights(const std::valarray<double> &x,
                    std::vector<std::valarray<double>> *W,
                    std::valarray<double> *D, double alpha, int R) {
    int j = 0, k = 0;
    int num_out = W->size();






    for (j = 0; j < num_out; j++) {


        (*D)[j] = (((*W)[j] - x) * ((*W)[j] - x)).sum();
    }



    auto result = std::min_element(std::begin(*D), std::end(*D));

    int d_min_idx = std::distance(std::begin(*D), result);


    int from_node = std::max(0, d_min_idx - R);
    int to_node = std::min(num_out, d_min_idx + R + 1);






    for (j = from_node; j < to_node; j++) {

        (*W)[j] += alpha * (x - (*W)[j]);
    }
}


void kohonen_som_tracer(const std::vector<std::valarray<double>> &X,
                        std::vector<std::valarray<double>> *W,
                        double alpha_min) {
    int num_samples = X.size();

    int num_out = W->size();
    int R = num_out >> 2, iter = 0;
    double alpha = 1.f;

    std::valarray<double> D(num_out);


    do {

        for (int sample = 0; sample < num_samples; sample++) {

            update_weights(X[sample], W, &D, alpha, R);
        }


        if (iter % 10 == 0 && R > 1) {
            R--;
        }

        alpha -= 0.01;
        iter++;
    } while (alpha > alpha_min);
}

}



using machine_learning::kohonen_som_tracer;


void test_circle(std::vector<std::valarray<double>> *data) {
    const int N = data->size();
    const double R = 0.75, dr = 0.3;
    double a_t = 0., b_t = 2.f * M_PI;
    double a_r = R - dr, b_r = R + dr;
    int i = 0;




    for (i = 0; i < N; i++) {
        double r = _random(a_r, b_r);
        double theta = _random(a_t, b_t);
        data[0][i][0] = r * cos(theta);
        data[0][i][1] = r * sin(theta);
    }
}


void test1() {
    int j = 0, N = 500;
    int features = 2;
    int num_out = 50;
    std::vector<std::valarray<double>> X(N);
    std::vector<std::valarray<double>> W(num_out);
    for (int i = 0; i < std::max(num_out, N); i++) {

        if (i < N) {
            X[i] = std::valarray<double>(features);
        }
        if (i < num_out) {
            W[i] = std::valarray<double>(features);




            for (j = 0; j < features; j++) {

                W[i][j] = _random(-1, 1);
            }
        }
    }

    test_circle(&X);
    save_nd_data("test1.csv", X);
    save_nd_data("w11.csv", W);
    kohonen_som_tracer(X, &W, 0.1);
    save_nd_data("w12.csv", W);
}


void test_lamniscate(std::vector<std::valarray<double>> *data) {
    const int N = data->size();
    const double dr = 0.2;
    int i = 0;




    for (i = 0; i < N; i++) {
        double dx = _random(-dr, dr);
        double dy = _random(-dr, dr);
        double theta = _random(0, M_PI);
        data[0][i][0] = dx + cos(theta);
        data[0][i][1] = dy + sin(2. * theta) / 2.f;
    }
}


void test2() {
    int j = 0, N = 500;
    int features = 2;
    int num_out = 20;
    std::vector<std::valarray<double>> X(N);
    std::vector<std::valarray<double>> W(num_out);
    for (int i = 0; i < std::max(num_out, N); i++) {

        if (i < N) {
            X[i] = std::valarray<double>(features);
        }
        if (i < num_out) {
            W[i] = std::valarray<double>(features);




            for (j = 0; j < features; j++) {

                W[i][j] = _random(-1, 1);
            }
        }
    }

    test_lamniscate(&X);
    save_nd_data("test2.csv", X);
    save_nd_data("w21.csv", W);
    kohonen_som_tracer(X, &W, 0.01);
    save_nd_data("w22.csv", W);
}


void test_3d_classes(std::vector<std::valarray<double>> *data) {
    const int N = data->size();
    const double R = 0.1;
    int i = 0;
    const int num_classes = 8;
    const std::array<const std::array<double, 3>, num_classes> centres = {

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
        int cls =
            std::rand() % num_classes;


        data[0][i][0] = _random(centres[cls][0] - R, centres[cls][0] + R);
        data[0][i][1] = _random(centres[cls][1] - R, centres[cls][1] + R);
        data[0][i][2] = _random(centres[cls][2] - R, centres[cls][2] + R);


    }
}


void test3() {
    int j = 0, N = 200;
    int features = 3;
    int num_out = 20;
    std::vector<std::valarray<double>> X(N);
    std::vector<std::valarray<double>> W(num_out);
    for (int i = 0; i < std::max(num_out, N); i++) {

        if (i < N) {
            X[i] = std::valarray<double>(features);
        }
        if (i < num_out) {
            W[i] = std::valarray<double>(features);




            for (j = 0; j < features; j++) {

                W[i][j] = _random(-1, 1);
            }
        }
    }

    test_3d_classes(&X);
    save_nd_data("test3.csv", X);
    save_nd_data("w31.csv", W);
    kohonen_som_tracer(X, &W, 0.01);
    save_nd_data("w32.csv", W);
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
