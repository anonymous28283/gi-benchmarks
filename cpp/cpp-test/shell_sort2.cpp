








template <class T>
void show_data(T *arr, size_t LEN) {
    size_t i;

    for (i = 0; i < LEN; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl;
}


template <typename T, size_t N>
void show_data(T (&arr)[N]) {
    show_data(arr, N);
}


namespace sorting {

template <typename T>
void shell_sort(T *arr, size_t LEN) {
    const unsigned int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};
    const unsigned int gap_len = 8;
    size_t i, j, g;

    for (g = 0; g < gap_len; g++) {
        unsigned int gap = gaps[g];
        for (i = gap; i < LEN; i++) {
            T tmp = arr[i];

            for (j = i; j >= gap && (arr[j - gap] - tmp) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }

            arr[j] = tmp;
        }
    }
}


template <typename T, size_t N>
void shell_sort(T (&arr)[N]) {
    shell_sort(arr, N);
}


template <typename T>
void shell_sort(std::vector<T> *arr) {
    shell_sort(arr->data(), arr->size());
}

}

using sorting::shell_sort;


template <typename T>
int compare(const void *a, const void *b) {
    T arg1 = *static_cast<const T *>(a);
    T arg2 = *static_cast<const T *>(b);

    if (arg1 < arg2)
        return -1;
    if (arg1 > arg2)
        return 1;
    return 0;



}


void test_int(const int NUM_DATA) {

    int *data = new int[NUM_DATA];
    int *data2 = new int[NUM_DATA];

    int range = 1800;

    for (int i = 0; i < NUM_DATA; i++)
        data[i] = data2[i] = (std::rand() % range) - (range >> 1);


    std::clock_t start = std::clock();
    shell_sort(data, NUM_DATA);
    std::clock_t end = std::clock();
    double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time spent sorting using shell_sort2: " << elapsed_time
              << "s\n";


    start = std::clock();
    std::qsort(data2, NUM_DATA, sizeof(data2[0]), compare<int>);
    end = std::clock();

    elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time spent sorting using std::qsort: " << elapsed_time
              << "s\n";

    for (int i = 0; i < NUM_DATA; i++) {
        assert(data[i] == data2[i]);

    }

    delete[] data;
    delete[] data2;
}


void test_f(const int NUM_DATA) {

    float *data = new float[NUM_DATA];
    float *data2 = new float[NUM_DATA];

    int range = 1000;

    for (int i = 0; i < NUM_DATA; i++) {
        data[i] = data2[i] = ((std::rand() % range) - (range >> 1)) / 100.;
    }


    std::clock_t start = std::clock();
    shell_sort(data, NUM_DATA);
    std::clock_t end = std::clock();
    double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time spent sorting using shell_sort2: " << elapsed_time
              << "s\n";


    start = std::clock();
    std::qsort(data2, NUM_DATA, sizeof(data2[0]), compare<float>);
    end = std::clock();

    elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time spent sorting using std::qsort: " << elapsed_time
              << "s\n";

    for (int i = 0; i < NUM_DATA; i++) {
        assert(data[i] == data2[i]);

    }

    delete[] data;
    delete[] data2;
}


int main(int argc, char *argv[]) {

    std::srand(std::time(NULL));

    test_int(100);
    std::cout << "Test 1 - 100 int values - passed. \n";
    test_int(1000);
    std::cout << "Test 2 - 1000 int values - passed.\n";
    test_int(10000);
    std::cout << "Test 3 - 10000 int values - passed.\n";

    test_f(100);
    std::cout << "Test 1 - 100 float values - passed. \n";
    test_f(1000);
    std::cout << "Test 2 - 1000 float values - passed.\n";
    test_f(10000);
    std::cout << "Test 3 - 10000 float values - passed.\n";

    int i, NUM_DATA;

    if (argc == 2)
        NUM_DATA = atoi(argv[1]);
    else
        NUM_DATA = 200;


    int *data = new int[NUM_DATA];

    int range = 1800;

    std::srand(time(NULL));
    for (i = 0; i < NUM_DATA; i++) {

        data[i] = (std::rand() % range) - (range >> 1);
    }

    std::cout << "Unsorted original data: " << std::endl;
    show_data(data, NUM_DATA);
    std::clock_t start = std::clock();
    shell_sort(data, NUM_DATA);
    std::clock_t end = std::clock();

    std::cout << std::endl
              << "Data Sorted using custom implementation: " << std::endl;
    show_data(data, NUM_DATA);

    double elapsed_time = (end - start) * 1.f / CLOCKS_PER_SEC;
    std::cout << "Time spent sorting: " << elapsed_time << "s\n" << std::endl;

    delete[] data;
    return 0;
}
