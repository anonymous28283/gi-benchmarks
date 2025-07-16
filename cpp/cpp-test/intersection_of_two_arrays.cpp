







namespace operations_on_datastructures {


void print(const std::vector<int32_t> &array) {
    for (int32_t i : array) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}


std::vector<int32_t> get_intersection(const std::vector<int32_t> &first,
                                      const std::vector<int32_t> &second) {
    std::vector<int32_t> res;
    size_t f_index = 0;
    size_t s_index = 0;
    size_t f_length = first.size();
    size_t s_length = second.size();

    while (f_index < f_length && s_index < s_length) {
        if (first[f_index] < second[s_index]) {
            f_index++;
        } else if (first[f_index] > second[s_index]) {
            s_index++;
        } else {
            if ((res.size() == 0) || (first[f_index] != res.back())) {
                res.push_back(
                    first[f_index]);
            }
            f_index++;
            s_index++;
        }
    }
    return res;
}

}


namespace tests {
using operations_on_datastructures::get_intersection;
using operations_on_datastructures::print;

void test1() {
    std::cout << "TEST CASE 1\n";
    std::cout << "Intialized a = {} b = {}\n";
    std::cout << "Expected result: {}\n";
    std::vector<int32_t> a = {};
    std::vector<int32_t> b = {};
    std::vector<int32_t> result = get_intersection(a, b);
    assert(result == a);
    print(result);
    std::cout << "TEST PASSED!\n\n";
}

void test2() {
    std::cout << "TEST CASE 2\n";
    std::cout << "Intialized a = {} b = {2, 3}\n";
    std::cout << "Expected result: {}\n";
    std::vector<int32_t> a = {};
    std::vector<int32_t> b = {2, 3};
    std::vector<int32_t> result = get_intersection(a, b);
    assert(result == a);
    print(result);
    std::cout << "TEST PASSED!\n\n";
}

void test3() {
    std::cout << "TEST CASE 3\n";
    std::cout << "Intialized a = {4, 6} b = {3, 6}\n";
    std::cout << "Expected result: {6}\n";
    std::vector<int32_t> a = {4, 6};
    std::vector<int32_t> b = {3, 6};
    std::vector<int32_t> result = get_intersection(a, b);
    std::vector<int32_t> expected = {6};
    assert(result == expected);
    print(result);
    std::cout << "TEST PASSED!\n\n";
}

void test4() {
    std::cout << "TEST CASE 4\n";
    std::cout << "Intialized a = {4, 6, 6, 6} b = {2, 4, 4, 6}\n";
    std::cout << "Expected result: {4, 6}\n";
    std::vector<int32_t> a = {4, 6, 6, 6};
    std::vector<int32_t> b = {2, 4, 4, 6};
    std::vector<int32_t> result = get_intersection(a, b);
    std::vector<int32_t> expected = {4, 6};
    assert(result == expected);
    print(result);
    std::cout << "TEST PASSED!\n\n";
}

void test5() {
    std::cout << "TEST CASE 5\n";
    std::cout << "Intialized a = {1, 2, 3, 4, 6, 7, 9} b = {2, 3, 4, 5}\n";
    std::cout << "Expected result: {2, 3, 4}\n";
    std::vector<int32_t> a = {1, 2, 3, 4, 6, 7, 9};
    std::vector<int32_t> b = {2, 3, 4, 5};
    std::vector<int32_t> result = get_intersection(a, b);
    std::vector<int32_t> expected = {2, 3, 4};
    assert(result == expected);
    print(result);
    std::cout << "TEST PASSED!\n\n";
}

void test6() {
    std::cout << "TEST CASE 6\n";
    std::cout << "Intialized a = {1, 3, 3, 2, 5, 9, 4, 7, 3, 2} ";
    std::cout << "b = {11, 3, 7, 8, 6}\n";
    std::cout << "Expected result: {3, 7}\n";
    std::vector<int32_t> a = {1, 3, 3, 2, 5, 9, 4, 7, 3, 2};
    std::vector<int32_t> b = {11, 3, 7, 8, 6};
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    std::vector<int32_t> result = get_intersection(a, b);
    std::vector<int32_t> expected = {3, 7};
    assert(result == expected);
    print(result);
    std::cout << "TEST PASSED!\n\n";
}
}


static void test() {
    tests::test1();
    tests::test2();
    tests::test3();
    tests::test4();
    tests::test5();
    tests::test6();
}


int main() {
    test();
    return 0;
}
