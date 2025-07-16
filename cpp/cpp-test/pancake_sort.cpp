







namespace sorting {

namespace pancake_sort {

template <typename T>
void reverse(std::vector<T> &arr, int start, int end) {
    T temp;
    while (start <= end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

template <typename T>
int pancakeSort(std::vector<T> &arr, int size) {
    for (int i = size; i > 1; --i) {
        int max_index = 0, j = 0;
        T max_value = 0;
        for (j = 0; j < i; j++) {
            if (arr[j] >= max_value) {
                max_value = arr[j];
                max_index = j;
            }
        }
        if (max_index != i - 1)
        {
            reverse(arr, 0, max_index);
            reverse(arr, 0, i - 1);
        }
    }
    return 0;
}
}
}


static void test() {

    const int size1 = 7;
    std::cout << "\nTest 1- as std::vector<int>...";
    std::vector<int> arr1 = {23, 10, 20, 11, 12, 6, 7};
    sorting::pancake_sort::pancakeSort(arr1, size1);
    assert(std::is_sorted(arr1.begin(), arr1.end()));
    std::cout << "Passed\n";
    for (int i = 0; i < size1; i++) {
        std::cout << arr1[i] << " ,";
    }
    std::cout << std::endl;


    const int size2 = 8;
    std::cout << "\nTest 2- as std::vector<double>...";
    std::vector<double> arr2 = {23.56, 10.62, 200.78, 111.484,
                                3.9,   1.2,   61.77,  79.6};
    sorting::pancake_sort::pancakeSort(arr2, size2);
    assert(std::is_sorted(arr2.begin(), arr2.end()));
    std::cout << "Passed\n";
    for (int i = 0; i < size2; i++) {
        std::cout << arr2[i] << ", ";
    }
    std::cout << std::endl;


    const int size3 = 7;
    std::cout << "\nTest 3- as std::vector<float>...";
    std::vector<float> arr3 = {6.56, 12.62, 200.78, 768.484, 19.27, 68.87, 9.6};
    sorting::pancake_sort::pancakeSort(arr3, size3);
    assert(std::is_sorted(arr3.begin(), arr3.end()));
    std::cout << "Passed\n";
    for (int i = 0; i < size3; i++) {
        std::cout << arr3[i] << ", ";
    }
    std::cout << std::endl;
}

int main() {
    test();
    return 0;
}
