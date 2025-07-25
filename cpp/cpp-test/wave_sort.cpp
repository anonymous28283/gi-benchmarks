







namespace sorting {

namespace wave_sort {

template <typename T>
std::vector<T> waveSort(const std::vector<T> &in_arr, int64_t n) {
    std::vector<T> arr(in_arr);

    for (int64_t i = 0; i < n; i++) {
        arr[i] = in_arr[i];
    }
    std::sort(arr.begin(), arr.end());
    for (int64_t i = 0; i < n - 1; i += 2) {
        std::swap(arr[i], arr[i + 1]);
    }
    return arr;
}
}
}


static void test() {

    std::vector<int64_t> array1 = {10, 90, 49, 2, 1, 5, 23};
    std::cout << "Test 1... ";
    std::vector<int64_t> arr1 = sorting::wave_sort::waveSort(array1, 7);
    const std::vector<int64_t> o1 = {2, 1, 10, 5, 49, 23, 90};
    assert(arr1 == o1);
    std::cout << "passed" << std::endl;


    std::vector<int64_t> array2 = {1, 3, 4, 2, 7, 8};
    std::cout << "Test 2... ";
    std::vector<int64_t> arr2 = sorting::wave_sort::waveSort(array2, 6);
    const std::vector<int64_t> o2 = {2, 1, 4, 3, 8, 7};
    assert(arr2 == o2);
    std::cout << "passed" << std::endl;


    std::vector<int64_t> array3 = {3, 3, 3, 3};
    std::cout << "Test 3... ";
    std::vector<int64_t> arr3 = sorting::wave_sort::waveSort(array3, 4);
    const std::vector<int64_t> o3 = {3, 3, 3, 3};
    assert(arr3 == o3);
    std::cout << "passed" << std::endl;


    std::vector<int64_t> array4 = {9, 4, 6, 8, 14, 3};
    std::cout << "Test 4... ";
    std::vector<int64_t> arr4 = sorting::wave_sort::waveSort(array4, 6);
    const std::vector<int64_t> o4 = {4, 3, 8, 6, 14, 9};
    assert(arr4 == o4);
    std::cout << "passed" << std::endl;
}


int main() {
    test();
    return 0;
}
