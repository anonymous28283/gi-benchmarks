








namespace sorting {

namespace cycle_sort {

template <typename T>
std::vector<T> cycleSort(const std::vector<T> &in_arr) {
    std::vector<T> arr(in_arr);
    for (int cycle_start = 0; cycle_start <= arr.size() - 1; cycle_start++) {

        T item = arr[cycle_start];



        int pos = cycle_start;
        for (int i = cycle_start + 1; i < arr.size(); i++) {
            if (arr[i] < item) {
                pos++;
            }
        }


        if (pos == cycle_start) {
            continue;
        }


        while (item == arr[pos]) pos += 1;
        if (pos == cycle_start) {
            continue;
        } else {
            std::swap(item, arr[pos]);
        }

        while (pos != cycle_start) {
            pos = cycle_start;

            for (size_t i = cycle_start + 1; i < arr.size(); i++) {
                if (arr[i] < item) {
                    pos += 1;
                }
            }

            while (item == arr[pos]) pos += 1;
            if (item == arr[pos]) {
                continue;
            } else {
                std::swap(item, arr[pos]);
            }
        }
    }
    return arr;
}
}
}


static void test() {


    std::vector<uint32_t> array1 = {4, 3, 2, 1};
    std::cout << "Test 1... ";
    std::vector<uint32_t> arr1 = sorting::cycle_sort::cycleSort(array1);
    assert(std::is_sorted(std::begin(arr1), std::end(arr1)));
    std::cout << "passed" << std::endl;


    std::vector<double> array2 = {4.3, -6.5, -7.4, 0, 2.7, 1.8};
    std::cout << "Test 2... ";
    std::vector<double> arr2 = sorting::cycle_sort::cycleSort(array2);
    assert(std::is_sorted(std::begin(arr2), std::end(arr2)));
    std::cout << "passed" << std::endl;



    std::vector<uint32_t> array3 = {3, 3, 3, 3};
    std::cout << "Test 3... ";
    std::vector<uint32_t> arr3 = sorting::cycle_sort::cycleSort(array3);
    assert(std::is_sorted(std::begin(arr3), std::end(arr3)));
    std::cout << "passed" << std::endl;


    std::vector<uint32_t> array4 = {3, 4, 6, 8, 9, 14};
    std::cout << "Test 4... ";
    std::vector<uint32_t> arr4 = sorting::cycle_sort::cycleSort(array4);
    assert(std::is_sorted(std::begin(arr4), std::end(arr4)));
    std::cout << "passed" << std::endl;
}


int main() {
    test();
    return 0;
}
