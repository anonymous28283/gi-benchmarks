






namespace range_queries {

namespace prefix_sum_array {

std::vector<int64_t> PSA(1, 0);


void build(std::vector<int64_t> original_array) {
    for (int i = 1; i <= static_cast<int>(original_array.size()); i++) {
        PSA.push_back(PSA[i - 1] + original_array[i]);
    }
}

int64_t query(int64_t beg, int64_t end) { return PSA[end] - PSA[beg - 1]; }

}
}


static void test() {
    std::vector<int64_t> values{0,  123, 0,  2,  -2, 5,
                                24, 0,   23, -1, -1};

    range_queries::prefix_sum_array::build(values);


    assert(range_queries::prefix_sum_array::query(1, 10) ==
           173);
    assert(range_queries::prefix_sum_array::query(4, 6) ==
           27);
    assert(range_queries::prefix_sum_array::query(5, 9) ==
           51);
}


int main() {
    test();
    return 0;
}
