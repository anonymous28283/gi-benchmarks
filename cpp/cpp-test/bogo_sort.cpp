








namespace sorting {

template <typename T, size_t N>
std::array <T, N> shuffle (std::array <T, N> arr) {
    for (int i = 0; i < N; i++) {

        std::swap(arr[i], arr[std::rand() % N]);
    }
    return arr;
}

template <typename T, size_t N>
std::array <T, N> randomized_bogosort (std::array <T, N> arr) {

    std::random_device random_device;
    std::mt19937 generator(random_device());
    while (!std::is_sorted(arr.begin(), arr.end())) {
        std::shuffle(arr.begin(), arr.end(), generator);
    }
    return arr;
}

}


template <typename T, size_t N>
void show_array (const std::array <T, N> &arr) {
    for (int x : arr) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}


void test() {

    std::array <int, 5> arr1;
    for (int &x : arr1) {
        x = std::rand() % 100;
    }
    std::cout << "Original Array : ";
    show_array(arr1);
    arr1 = sorting::randomized_bogosort(arr1);
    std::cout << "Sorted Array : ";
    show_array(arr1);
    assert(std::is_sorted(arr1.begin(), arr1.end()));

    std::array <int, 5> arr2;
    for (int &x : arr2) {
        x = std::rand() % 100;
    }
    std::cout << "Original Array : ";
    show_array(arr2);
    arr2 = sorting::randomized_bogosort(arr2);
    std::cout << "Sorted Array : ";
    show_array(arr2);
    assert(std::is_sorted(arr2.begin(), arr2.end()));
}


int main() {

    test();

    std::array <int, 5> arr = {3, 7, 10, 4, 1};
    std::cout << "Original Array : ";
    show_array(arr);
    arr = sorting::randomized_bogosort(arr);
    std::cout << "Sorted Array : ";
    show_array(arr);
    return 0;
}
