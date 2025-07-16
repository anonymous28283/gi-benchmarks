







namespace backtracking {

namespace subset_sum {

uint64_t number_of_subsets(int32_t sum, const std::vector<int32_t> &in_arr) {
    int32_t nelement = in_arr.size();
    uint64_t count_of_subset = 0;

    for (int32_t i = 0; i < (1 << (nelement)); i++) {
        int32_t check = 0;
        for (int32_t j = 0; j < nelement; j++) {
            if (i & (1 << j)) {
                check += (in_arr[j]);
            }
        }
        if (check == sum) {
            count_of_subset++;
        }
    }
    return count_of_subset;
}
}
}


static void test() {

    std::cout << "1st test ";
    std::vector<int32_t> array1 = {-7, -3, -2, 5, 8};
    assert(backtracking::subset_sum::number_of_subsets(0, array1) ==
           2);

    std::cout << "passed" << std::endl;


    std::cout << "2nd test ";
    std::vector<int32_t> array2 = {1, 2, 3, 3};
    assert(backtracking::subset_sum::number_of_subsets(6, array2) ==
           3);

    std::cout << "passed" << std::endl;


    std::cout << "3rd test ";
    std::vector<int32_t> array3 = {1, 1, 1, 1};
    assert(backtracking::subset_sum::number_of_subsets(1, array3) ==
           4);

    std::cout << "passed" << std::endl;


    std::cout << "4th test ";
    std::vector<int32_t> array4 = {3, 3, 3, 3};
    assert(backtracking::subset_sum::number_of_subsets(6, array4) ==
           6);

    std::cout << "passed" << std::endl;


    std::cout << "5th test ";
    std::vector<int32_t> array5 = {};
    assert(backtracking::subset_sum::number_of_subsets(6, array5) ==
           0);

    std::cout << "passed" << std::endl;
}


int main() {
    test();
    return 0;
}
