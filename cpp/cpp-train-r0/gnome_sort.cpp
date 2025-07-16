







namespace sorting {

template <typename T>
void gnomeSort(T *arr, int size) {

    if (size <= 1) {
        return;
    }

    int index = 0;
    while (index < size) {

        if ((index == 0) || (arr[index] >= arr[index - 1])) {
            index++;
        } else {
            std::swap(arr[index], arr[index - 1]);
            index--;
        }
    }
}


template <typename T, size_t size>
std::array<T, size> gnomeSort(std::array<T, size> arr) {

    if (size <= 1) {
        return arr;
    }

    int index = 0;
    while (index < size) {

        if ((index == 0) || (arr[index] >= arr[index - 1])) {
            index++;
        } else {
            std::swap(arr[index], arr[index - 1]);
            index--;
        }
    }
    return arr;
}
}


static void test() {

    std::cout << "Test 1 - as a C-array...";
    const int size = 6;
    std::array<int, size> arr = {-22, 100, 150, 35, -10, 99};
    sorting::gnomeSort(arr.data(),
                       size);
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
    std::cout << " Passed\n";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl;


    std::cout << "\nTest 2 - as a std::array...";
    std::array<double, size> double_arr = {-100.2, 10.2, 20.0, 9.0, 7.5, 7.2};
    std::array<double, size> sorted_arr = sorting::gnomeSort(double_arr);
    assert(std::is_sorted(std::begin(sorted_arr), std::end(sorted_arr)));
    std::cout << " Passed\n";
    for (int i = 0; i < size; i++) {
        std::cout << double_arr[i] << ", ";
    }
    std::cout << std::endl;


    std::cout << "\nTest 3 - 200 random numbers as a std::array...";
    const int size2 = 200;
    std::array<float, size2> rand_arr{};

    for (auto &a : rand_arr) {

        a = float(std::rand() % 1000 - 500) / 100.f;
    }

    std::array<float, size2> float_arr = sorting::gnomeSort(rand_arr);
    assert(std::is_sorted(std::begin(float_arr), std::end(float_arr)));
    std::cout << " Passed\n";

    std::cout << std::endl;
}


int main() {
    test();
    return 0;
}
