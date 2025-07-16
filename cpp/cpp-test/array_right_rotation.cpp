






namespace operations_on_datastructures {


void print(const std::vector<int32_t> &array) {
    for (int32_t i : array) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}


std::vector<int32_t> shift_right(const std::vector<int32_t> &array,
                                 size_t shift) {
    if (array.size() <= shift) {
        return {};
    }
    std::vector<int32_t> res(array.size());
    for (size_t i = shift; i < array.size(); i++) {
        res[i] = array[i - shift];
    }
    for (size_t i = 0; i < shift; i++) {
        res[i] =
            array[array.size() - shift + i];
    }
    return res;
}

}


namespace tests {
using operations_on_datastructures::print;
using operations_on_datastructures::shift_right;

void test1() {
    std::cout << "TEST CASE 1\n";
    std::cout << "Initialized arr = {1, 2, 3, 4, 5}\n";
    std::cout << "Expected result: {4, 5, 1, 2, 3}\n";
    std::vector<int32_t> arr = {1, 2, 3, 4, 5};
    std::vector<int32_t> res = shift_right(arr, 2);
    std::vector<int32_t> expected = {4, 5, 1, 2, 3};
    assert(res == expected);
    print(res);
    std::cout << "TEST PASSED!\n\n";
}

void test2() {
    std::cout << "TEST CASE 2\n";
    std::cout << "Initialized arr = {}\n";
    std::cout << "Expected result: {}\n";
    std::vector<int32_t> arr = {};
    std::vector<int32_t> res = shift_right(arr, 2);
    std::vector<int32_t> expected = {};
    assert(res == expected);
    print(res);
    std::cout << "TEST PASSED!\n\n";
}

void test3() {
    std::cout << "TEST CASE 3\n";
    std::cout << "Initialized arr = {1, 2, 3, 4, 5}\n";
    std::cout << "Expected result: {}\n";
    std::vector<int32_t> arr = {1, 2, 3, 4, 5};
    std::vector<int32_t> res = shift_right(arr, 7);
    std::vector<int32_t> expected = {};
    assert(res == expected);
    print(res);
    std::cout << "TEST PASSED!\n\n";
}

void test4() {
    std::cout << "TEST CASE 4\n";
    std::cout << "Initialized arr = {2, 4, ..., 420}\n";
    std::cout << "Expected result: {420, 2, 4, ..., 418}\n";
    std::vector<int32_t> arr;
    for (int i = 1; i <= 210; i++) {
        arr.push_back(i * 2);
    }
    print(arr);
    std::vector<int32_t> res = shift_right(arr, 1);
    std::vector<int32_t> expected;
    expected.push_back(420);
    for (int i = 0; i < 209; i++) {
        expected.push_back(arr[i]);
    }
    assert(res == expected);
    print(res);
    std::cout << "TEST PASSED!\n\n";
}

void test5() {
    std::cout << "TEST CASE 5\n";
    std::cout << "Initialized arr = {1, 2, 3, 4, 5}\n";
    std::cout << "Expected result: {1, 2, 3, 4, 5}\n";
    std::vector<int32_t> arr = {1, 2, 3, 4, 5};
    std::vector<int32_t> res = shift_right(arr, 0);
    assert(res == arr);
    print(res);
    std::cout << "TEST PASSED!\n\n";
}
}


static void test() {
    tests::test1();
    tests::test2();
    tests::test3();
    tests::test4();
    tests::test5();
}


int main() {
    test();
    return 0;
}
