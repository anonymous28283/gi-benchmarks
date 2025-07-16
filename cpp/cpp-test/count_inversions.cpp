






namespace sorting {

namespace inversion {








template <typename T>
uint32_t merge(T* arr, T* temp, uint32_t left, uint32_t mid, uint32_t right) {
    uint32_t i = left;
    uint32_t j = mid + 1;
    uint32_t k = left;
    uint32_t inv_count = 0;

    while ((i <= mid) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count +=
                (mid - i +
                 1);
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (k = left; k <= right; k++) {
        arr[k] = temp[k];
    }
    return inv_count;
}


template <typename T>
uint32_t mergeSort(T* arr, T* temp, uint32_t left, uint32_t right) {
    uint32_t mid = 0, inv_count = 0;
    if (right > left) {

        mid = (right + left) / 2;

        inv_count += mergeSort(arr, temp, left, mid);
        inv_count += mergeSort(arr, temp, mid + 1, right);


        inv_count += merge(arr, temp, left, mid, right);
    }
    return inv_count;
}


template <class T>
uint32_t countInversion(T* arr, const uint32_t size) {
    std::vector<T> temp;
    temp.reserve(size);
    temp.assign(size, 0);
    return mergeSort(arr, temp.data(), 0, size - 1);
}


template <typename T>
void show(T* arr, const uint32_t array_size) {
    std::cout << "Printing array: \n";
    for (uint32_t i = 0; i < array_size; i++) {
        std::cout << " " << arr[i];
    }
    std::cout << "\n";
}

}
}


static void test() {

    std::vector<uint64_t> arr1 = {
        100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84,
        83,  82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67,
        66,  65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50,
        49,  48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33,
        32,  31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,
        15,  14, 13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1};
    uint32_t size1 = arr1.size();
    uint32_t inv_count1 = 4950;
    uint32_t result1 = sorting::inversion::countInversion(arr1.data(), size1);
    assert(inv_count1 == result1);

    std::vector<int> arr2 = {22, 66, 75, 23, 11, 87, 2, 44, 98, 43};
    uint32_t size2 = arr2.size();
    uint32_t inv_count2 = 20;
    uint32_t result2 = sorting::inversion::countInversion(arr2.data(), size2);
    assert(inv_count2 == result2);

    std::vector<double> arr3 = {33.1, 45.2, 65.4, 76.5, 1.0,
                                2.9,  5.4,  7.7,  88.9, 12.4};
    uint32_t size3 = arr3.size();
    uint32_t inv_count3 = 21;
    uint32_t result3 = sorting::inversion::countInversion(arr3.data(), size3);
    assert(inv_count3 == result3);

    std::vector<char> arr4 = {'a', 'b', 'c', 'd', 'e'};
    uint32_t size4 = arr4.size();
    uint32_t inv_count4 = 0;
    uint32_t result4 = sorting::inversion::countInversion(arr4.data(), size4);
    assert(inv_count4 == result4);
}






































int main() {
    test();

    return 0;
}
