









using qr_algorithm::qr_decompose;
using qr_algorithm::operator<<;


int main(void) {
    unsigned int ROWS, COLUMNS;

    std::cout << "Enter the number of rows and columns: ";
    std::cin >> ROWS >> COLUMNS;

    std::cout << "Enter matrix elements row-wise:\n";

    std::valarray<std::valarray<double>> A(ROWS);
    std::valarray<std::valarray<double>> Q(ROWS);
    std::valarray<std::valarray<double>> R(COLUMNS);
    for (int i = 0; i < std::max(ROWS, COLUMNS); i++) {
        if (i < ROWS) {
            A[i] = std::valarray<double>(COLUMNS);
            Q[i] = std::valarray<double>(COLUMNS);
        }
        if (i < COLUMNS) {
            R[i] = std::valarray<double>(COLUMNS);
        }
    }

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLUMNS; j++) std::cin >> A[i][j];

    std::cout << A << "\n";

    clock_t t1 = clock();
    qr_decompose(A, &Q, &R);
    double dtime = static_cast<double>(clock() - t1) / CLOCKS_PER_SEC;

    std::cout << Q << "\n";
    std::cout << R << "\n";
    std::cout << "Time taken to compute: " << dtime << " sec\n ";

    return 0;
}
