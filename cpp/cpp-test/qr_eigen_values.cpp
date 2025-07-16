










using qr_algorithm::operator<<;




void create_matrix(std::valarray<std::valarray<double>> *A) {
    int i, j, tmp, lim2 = LIMS >> 1;
    int N = A->size();




    for (i = 0; i < N; i++) {
        A[0][i][i] = (std::rand() % LIMS) - lim2;
        for (j = i + 1; j < N; j++) {
            tmp = (std::rand() % LIMS) - lim2;
            A[0][i][j] = tmp;
            A[0][j][i] = tmp;
        }
    }
}


void mat_mul(const std::valarray<std::valarray<double>> &A,
             const std::valarray<std::valarray<double>> &B,
             std::valarray<std::valarray<double>> *OUT) {
    int R1 = A.size();
    int C1 = A[0].size();
    int R2 = B.size();
    int C2 = B[0].size();
    if (C1 != R2) {
        perror("Matrix dimensions mismatch!");
        return;
    }

    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C2; j++) {
            OUT[0][i][j] = 0.f;
            for (int k = 0; k < C1; k++) {
                OUT[0][i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

namespace qr_algorithm {

std::valarray<double> eigen_values(std::valarray<std::valarray<double>> *A,
                                   bool print_intermediates = false) {
    int rows = A->size();
    int columns = rows;
    int counter = 0, num_eigs = rows - 1;
    double last_eig = 0;

    std::valarray<std::valarray<double>> Q(rows);
    std::valarray<std::valarray<double>> R(columns);


    std::valarray<double> eigen_vals(rows);
    for (int i = 0; i < rows; i++) {
        Q[i] = std::valarray<double>(columns);
        R[i] = std::valarray<double>(columns);
    }


    while (num_eigs > 0) {

        while (std::abs(A[0][num_eigs][num_eigs - 1]) >
               std::numeric_limits<double>::epsilon()) {

            last_eig = A[0][num_eigs][num_eigs];
            for (int i = 0; i < rows; i++) {
                A[0][i][i] -= last_eig;
            }

            qr_decompose(*A, &Q, &R);

            if (print_intermediates) {
                std::cout << *A << "\n";
                std::cout << Q << "\n";
                std::cout << R << "\n";
                printf("-------------------- %d ---------------------\n",
                       ++counter);
            }


            mat_mul(R, Q, A);

            for (int i = 0; i < rows; i++) {
                A[0][i][i] += last_eig;
            }
        }


        eigen_vals[num_eigs] = last_eig;

        if (print_intermediates) {
            std::cout << "========================\n";
            std::cout << "Eigen value: " << last_eig << ",\n";
            std::cout << "========================\n";
        }

        num_eigs--;
        rows--;
        columns--;
    }
    eigen_vals[0] = A[0][0][0];

    if (print_intermediates) {
        std::cout << Q << "\n";
        std::cout << R << "\n";
    }

    return eigen_vals;
}

}


void test1() {
    std::valarray<std::valarray<double>> X = {{5, 7}, {7, 11}};
    double y[] = {15.56158, 0.384227};

    std::cout << "------- Test 1 -------" << std::endl;
    std::valarray<double> eig_vals = qr_algorithm::eigen_values(&X);

    for (int i = 0; i < 2; i++) {
        std::cout << i + 1 << "/2 Checking for " << y[i] << " --> ";
        bool result = false;
        for (int j = 0; j < 2 && !result; j++) {
            if (std::abs(y[i] - eig_vals[j]) < 0.1) {
                result = true;
                std::cout << "(" << eig_vals[j] << ") ";
            }
        }
        assert(result);
        std::cout << "found\n";
    }
    std::cout << "Test 1 Passed\n\n";
}


void test2() {
    std::valarray<std::valarray<double>> X = {{-4, 4, 2, 0, -3},
                                              {4, -4, 4, -3, -1},
                                              {2, 4, 4, 3, -3},
                                              {0, -3, 3, -1, -3},
                                              {-3, -1, -3, -3, 0}};
    double y[] = {9.27648, -9.26948, 2.0181, -1.03516,
                  -5.98994};

    std::cout << "------- Test 2 -------" << std::endl;
    std::valarray<double> eig_vals = qr_algorithm::eigen_values(&X);

    std::cout << X << "\n"
              << "Eigen values: " << eig_vals << "\n";

    for (int i = 0; i < 5; i++) {
        std::cout << i + 1 << "/5 Checking for " << y[i] << " --> ";
        bool result = false;
        for (int j = 0; j < 5 && !result; j++) {
            if (std::abs(y[i] - eig_vals[j]) < 0.1) {
                result = true;
                std::cout << "(" << eig_vals[j] << ") ";
            }
        }
        assert(result);
        std::cout << "found\n";
    }
    std::cout << "Test 2 Passed\n\n";
}


int main(int argc, char **argv) {
    int mat_size = 5;
    if (argc == 2) {
        mat_size = atoi(argv[1]);
    } else {
        test1();
        test2();
        std::cout << "Usage: ./qr_eigen_values [mat_size]\n";
        return 0;
    }

    if (mat_size < 2) {
        fprintf(stderr, "Matrix size should be > 2\n");
        return -1;
    }


    std::srand(std::time(nullptr));

    int i, rows = mat_size, columns = mat_size;

    std::valarray<std::valarray<double>> A(rows);

    for (int i = 0; i < rows; i++) {
        A[i] = std::valarray<double>(columns);
    }


    create_matrix(&A);

    std::cout << A << "\n";

    clock_t t1 = clock();
    std::valarray<double> eigen_vals = qr_algorithm::eigen_values(&A);
    double dtime = static_cast<double>(clock() - t1) / CLOCKS_PER_SEC;

    std::cout << "Eigen vals: ";
    for (i = 0; i < mat_size; i++) std::cout << eigen_vals[i] << "\t";
    std::cout << "\nTime taken to compute: " << dtime << " sec\n";

    return 0;
}
