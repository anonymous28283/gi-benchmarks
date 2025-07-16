







namespace sorting {


std::vector<uint64_t> selectionSort(const std::vector<uint64_t> &arr,
                                    uint64_t len) {
    std::vector<uint64_t> array(
        arr.begin(),
        arr.end());
    for (uint64_t it = 0; it < len; ++it) {
        uint64_t min = it;
        for (uint64_t it2 = it + 1; it2 < len; ++it2) {
            if (array[it2] < array[min]) {
                min = it2;
            }
        }

        if (min != it) {
            uint64_t tmp = array[min];
            array[min] = array[it];
            array[it] = tmp;
        }
    }

    return array;
}
}


static void test() {


    std::vector<uint64_t> vector1 = {1, 0, 0, 1, 1, 0, 2, 1};
    uint64_t vector1size = vector1.size();
    std::cout << "1st test... ";
    std::vector<uint64_t> result_test1;
    result_test1 = sorting::selectionSort(vector1, vector1size);
    assert(std::is_sorted(result_test1.begin(), result_test1.end()));
    std::cout << "Passed" << std::endl;




    std::vector<uint64_t> vector2 = {19, 22, 540, 241, 156, 140, 12, 1};
    uint64_t vector2size = vector2.size();
    std::cout << "2nd test... ";
    std::vector<uint64_t> result_test2;
    result_test2 = sorting::selectionSort(vector2, vector2size);
    assert(std::is_sorted(result_test2.begin(), result_test2.end()));
    std::cout << "Passed" << std::endl;



    std::vector<uint64_t> vector3 = {11, 20, 30, 41, 15, 60, 82, 15};
    uint64_t vector3size = vector3.size();
    std::cout << "3rd test... ";
    std::vector<uint64_t> result_test3;
    result_test3 = sorting::selectionSort(vector3, vector3size);
    assert(std::is_sorted(result_test3.begin(), result_test3.end()));
    std::cout << "Passed" << std::endl;




    std::vector<uint64_t> vector4 = {1, 9, 11, 546, 26, 65, 212, 14};
    uint64_t vector4size = vector2.size();
    std::cout << "4th test... ";
    std::vector<uint64_t> result_test4;
    result_test4 = sorting::selectionSort(vector4, vector4size);
    assert(std::is_sorted(result_test4.begin(), result_test4.end()));
    std::cout << "Passed" << std::endl;
}


int main() {
    test();
    return 0;
}
