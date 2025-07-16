









namespace sorting {


template <typename T>
void recursive_bubble_sort(std::vector<T> *nums, uint64_t n) {
    if (n == 1) {
        return;
    }

    for (uint64_t i = 0; i < n - 1; i++) {

        if ((*nums)[i] > (*nums)[i + 1]) {
            std::swap((*nums)[i], (*nums)[i + 1]);
        }
    }


    recursive_bubble_sort(nums, n - 1);
}
}


static void test() {

    std::cout << "1st test using `int`\n";
    const uint64_t size = 6;
    std::vector<int64_t> arr;

    arr.push_back(22);
    arr.push_back(46);
    arr.push_back(94);
    arr.push_back(12);
    arr.push_back(37);
    arr.push_back(63);


    sorting::recursive_bubble_sort(&arr, size);
    assert(std::is_sorted(std::begin(arr), std::end(arr)));
    std::cout << " 1st test passed!\n";

    for (uint64_t i = 0; i < size; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << std::endl;


    std::cout << "2nd test using doubles\n";
    std::vector<double> double_arr;


    double_arr.push_back(20.4);
    double_arr.push_back(62.7);
    double_arr.push_back(12.2);
    double_arr.push_back(43.6);
    double_arr.push_back(74.1);
    double_arr.push_back(57.9);


    sorting::recursive_bubble_sort(&double_arr, size);
    assert(std::is_sorted(std::begin(double_arr), std::end(double_arr)));
    std::cout << " 2nd test passed!\n";

    for (uint64_t i = 0; i < size; i++) {
        std::cout << double_arr[i] << ", ";
    }
    std::cout << std::endl;
}


int main() {
    test();
    return 0;
}
