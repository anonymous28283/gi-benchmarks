








namespace sorting {

namespace dnf_sort {

template <typename T>
std::vector<T> dnfSort(const std::vector<T> &in_arr) {
    std::vector<T> arr(in_arr);
    uint64_t lo = 0;
    uint64_t hi = arr.size() - 1;
    uint64_t mid = 0;



    while (mid <= hi) {
        switch (arr[mid]) {

            case 0:
                std::swap(arr[lo++], arr[mid++]);
                break;


            case 1:
                mid++;
                break;


            case 2:
                std::swap(arr[mid], arr[hi--]);
                break;
        }
    }
    return arr;
}
}
}


static void test() {


    std::vector<uint64_t> array1 = {0, 1, 1, 2};
    std::cout << "Test 1... ";
    std::vector<uint64_t> arr1 = sorting::dnf_sort::dnfSort(array1);
    assert(std::is_sorted(std::begin(arr1), std::end(arr1)));
    std::cout << "passed" << std::endl;


    std::vector<uint64_t> array2 = {1, 0, 0, 1, 1, 0, 2, 1};
    std::cout << "Test 2... ";
    std::vector<uint64_t> arr2 = sorting::dnf_sort::dnfSort(array2);
    assert(std::is_sorted(std::begin(arr2), std::end(arr2)));
    std::cout << "passed" << std::endl;


    std::vector<uint64_t> array3 = {1, 1, 0, 0, 1, 2, 2, 0, 2, 1};
    std::cout << "Test 3... ";
    std::vector<uint64_t> arr3 = sorting::dnf_sort::dnfSort(array3);
    assert(std::is_sorted(std::begin(arr3), std::end(arr3)));
    std::cout << "passed" << std::endl;


    std::vector<uint64_t> array4 = {2, 2, 2, 0, 0, 1, 1};
    std::cout << "Test 4... ";
    std::vector<uint64_t> arr4 = sorting::dnf_sort::dnfSort(array4);
    assert(std::is_sorted(std::begin(arr4), std::end(arr4)));
    std::cout << "passed" << std::endl;
}


int main() {
    test();
    return 0;
}
