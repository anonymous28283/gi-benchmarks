







namespace sorting {


template <std::size_t N>
std::array<int, N> pigeonSort(std::array<int, N> arr) {

    auto min = std::min_element(std::begin(arr), std::end(arr));
    auto max = std::max_element(std::begin(arr), std::end(arr));


    int range = *max - *min + 1;
    int *hole = new int[range]();


    for (int i = 0; i < N; i++) {
        hole[arr[i] - *min] = arr[i];
    }


    int count = 0;
    for (int i = 0; i < range; i++) {
        while (hole[i] != '\0') {
            arr[count] = hole[i];
            hole[i] = {};
            count++;
        }
    }
    delete[] hole;

    return arr;
}
}


static void test_1() {
    const int n = 7;
    std::array<int, n> test_array = {8, 3, 2, 7, 4, 6, 8};

    test_array = sorting::pigeonSort<n>(test_array);

    assert(std::is_sorted(std::begin(test_array), std::end(test_array)));


    for (int i = 0; i < n; i++) {
        std::cout << test_array.at(i) << " ";
    }
    std::cout << "\nPassed\n";
}


static void test_2() {
    const int n = 10;
    std::array<int, n> test_array = {802, 630, 20,  745, 52,
                                     300, 612, 932, 78,  187};

    test_array = sorting::pigeonSort<n>(test_array);

    assert(std::is_sorted(std::begin(test_array), std::end(test_array)));


    for (int i = 0; i < n; i++) {
        std::cout << test_array.at(i) << " ";
    }
    std::cout << "\nPassed\n";
}


static void test_3() {
    const int n = 4;
    std::array<int, n> test_array = {11, 13, 12, 14};

    test_array = sorting::pigeonSort<n>(test_array);

    assert(std::is_sorted(std::begin(test_array), std::end(test_array)));


    for (int i = 0; i < n; i++) {
        std::cout << test_array.at(i) << " ";
    }
    std::cout << "\nPassed\n";
}


int main() {
    test_1();
    test_2();
    test_3();

    return 0;
}
