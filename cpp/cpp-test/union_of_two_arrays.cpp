







namespace operations_on_datastructures {


void print(const std::vector<int32_t> &array) {
    for (int32_t i : array) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}


std::vector<int32_t> get_union(const std::vector<int32_t> &first,
                               const std::vector<int32_t> &second) {
    std::vector<int32_t> res;
    size_t f_index = 0;
    size_t s_index = 0;
    size_t f_length = first.size();
    size_t s_length = second.size();
    int32_t next = 0;

    while (f_index < f_length && s_index < s_length) {
        if (first[f_index] < second[s_index]) {
            next = first[f_index];
            f_index++;
        } else if (first[f_index] > second[s_index]) {
            next = second[s_index];
            s_index++;
        } else {
            next = first[f_index];
            f_index++;
            s_index++;
        }
        if ((res.size() == 0) || (next != res.back())) {
            res.push_back(next);
        }
    }
    while (f_index < f_length) {
        next = first[f_index];
        if ((res.size() == 0) || (next != res.back())) {
            res.push_back(next);
        }
        f_index++;
    }
    while (s_index < s_length) {
        next = second[s_index];
        if ((res.size() == 0) || (next != res.back())) {
            res.push_back(next);
        }
        s_index++;
    }
    return res;
}

}


namespace tests {
using operations_on_datastructures::get_union;
using operations_on_datastructures::print;

void test1() {
    std::cout << "TEST CASE 1\n";
    std::cout << "Intialized a = {} b = {}\n";
    std::cout << "Expected result: {}\n";
    std::vector<int32_t> a = {};
    std::vector<int32_t> b = {};
    std::vector<int32_t> result = get_union(a, b);
    assert(result == a);
    print(result);
    std::cout << "TEST PASSED!\n\n";
}

void test2() {
    std::cout << "TEST CASE 2\n";
    std::cout << "Intialized a = {} b = {2, 3}\n";
    std::cout << "Expected result: {2, 3}\n";
    std::vector<int32_t> a = {};
    std::vector<int32_t> b = {2, 3};
    std::vector<int32_t> result = get_union(a, b);
    assert(result == b);
    print(result);
    std::cout << "TEST PASSED!\n\n";
}

void test3() {
    std::cout << "TEST CASE 3\n";
    std::cout << "Intialized a = {4, 6} b = {2, 3}\n";
    std::cout << "Expected result: {2, 3, 4, 6}\n";
    std::vector<int32_t> a = {4, 6};
    std::vector<int32_t> b = {2, 3};
    std::vector<int32_t> result = get_union(a, b);
    std::vector<int32_t> expected = {2, 3, 4, 6};
    assert(result == expected);
    print(result);
    std::cout << "TEST PASSED!\n\n";
}

void test4() {
    std::cout << "TEST CASE 4\n";
    std::cout << "Intialized a = {4, 6, 6, 7} b = {2, 3, 4}\n";
    std::cout << "Expected result: {2, 3, 4, 6, 7}\n";
    std::vector<int32_t> a = {4, 6, 6, 7};
    std::vector<int32_t> b = {2, 3, 4};
    std::vector<int32_t> result = get_union(a, b);
    std::vector<int32_t> expected = {2, 3, 4, 6, 7};
    assert(result == expected);
    print(result);
    std::cout << "TEST PASSED!\n\n";
}

void test5() {
    std::cout << "TEST CASE 5\n";
    std::cout << "Intialized a = {1, 4, 6, 7, 9} b = {2, 3, 5}\n";
    std::cout << "Expected result: {1, 2, 3, 4, 5, 6, 7, 9}\n";
    std::vector<int32_t> a = {1, 4, 6, 7, 9};
    std::vector<int32_t> b = {2, 3, 5};
    std::vector<int32_t> result = get_union(a, b);
    std::vector<int32_t> expected = {1, 2, 3, 4, 5, 6, 7, 9};
    assert(result == expected);
    print(result);
    std::cout << "TEST PASSED!\n\n";
}

void test6() {
    std::cout << "TEST CASE 6\n";
    std::cout << "Intialized a = {1, 3, 3, 2, 5, 9, 4, 3, 2} ";
    std::cout << "b = {11, 3, 7, 8, 6}\n";
    std::cout << "Expected result: {1, 2, 3, 4, 5, 6, 7, 8, 9, 11}\n";
    std::vector<int32_t> a = {1, 3, 3, 2, 5, 9, 4, 3, 2};
    std::vector<int32_t> b = {11, 3, 7, 8, 6};
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    std::vector<int32_t> result = get_union(a, b);
    std::vector<int32_t> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
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
