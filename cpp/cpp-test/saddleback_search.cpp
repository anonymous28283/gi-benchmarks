






namespace search {

namespace saddleback {

std::pair<uint32_t, uint32_t> saddleback(
    std::vector<std::vector<int32_t>> matrix, int32_t element) {
    uint32_t left_index = 0;
    uint32_t right_index = matrix[0].size() - 1;
    while (left_index <
           matrix.size()) {
        if (element ==
            matrix[left_index]
                  [right_index]) {

            return std::make_pair(left_index + 1, right_index + 1);
        } else if (element >
                   matrix[left_index]
                         [right_index]) {


            ++left_index;
        } else if (element <
                   matrix[left_index]
                         [right_index]) {


            if (!right_index)
                break;
            else
                --right_index;
        }
    }
    return std::make_pair(
        0, 0);

}
}
}


static void test() {
    std::vector<std::vector<int32_t>> matrix = {{1, 10, 100, 1000, 10000},
                                                {2, 20, 200, 2000, 20000},
                                                {3, 30, 300, 3000, 30000},
                                                {4, 40, 400, 4000, 40000},
                                                {5, 50, 500, 5000, 50000}};

    std::pair<uint32_t, uint32_t> not_found = std::make_pair(0, 0);
    std::pair<uint32_t, uint32_t> test_answer;

    std::pair<uint32_t, uint32_t> answer1 =
        search::saddleback::saddleback(matrix, 123);
    assert(not_found == answer1);

    answer1 = search::saddleback::saddleback(matrix, 0);
    assert(not_found == answer1);

    answer1 = search::saddleback::saddleback(matrix, 1);
    test_answer = std::make_pair(1, 1);
    assert(test_answer == answer1);

    answer1 = search::saddleback::saddleback(matrix, 50000);
    test_answer = std::make_pair(5, 5);
    assert(test_answer == answer1);

    answer1 = search::saddleback::saddleback(matrix, 300);
    test_answer = std::make_pair(3, 3);
    assert(test_answer == answer1);
}


int main() {
    test();
    return 0;
}
