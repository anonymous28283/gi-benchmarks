










namespace sorting {

namespace radix_sort {

std::vector<uint64_t> step_ith(
    uint16_t cur_digit,
    const std::vector<uint64_t>& ar) {
    int n = ar.size();
    std::vector<uint32_t> position(10, 0);
    for (int i = 0; i < n; ++i) {
        position[(ar[i] / cur_digit) %
                 10]++;
    }
    int cur = 0;
    for (int i = 0; i < 10; ++i) {
        int a = position[i];
        position[i] = cur;
        cur += a;
    }
    std::vector<uint64_t> temp(n);
    for (int i = 0; i < n; ++i) {
        temp[position[(ar[i] / cur_digit) % 10]] =
            ar[i];

        position[(ar[i] / cur_digit) %
                 10]++;

    }
    return temp;
}

std::vector<uint64_t> radix(const std::vector<uint64_t>& ar) {
    uint64_t max_ele =
        *max_element(ar.begin(), ar.end());
    std::vector<uint64_t> temp = ar;
    for (int i = 1; max_ele / i > 0;
         i *= 10) {

        temp = step_ith(i, temp);
    }
    for (uint64_t i : temp) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    return temp;
}
}
}


static void tests() {

    std::vector<uint64_t> ar1 = {432, 234, 143, 332, 123};
    ar1 = sorting::radix_sort::radix(ar1);
    assert(std::is_sorted(ar1.begin(), ar1.end()));

    std::vector<uint64_t> ar2 = {213, 3214, 123, 111, 112, 142,
                                 133, 132,  32,  12,  113};
    ar2 = sorting::radix_sort::radix(ar2);
    assert(std::is_sorted(ar2.begin(), ar2.end()));
}

int main() {
    tests();
    return 0;
}
