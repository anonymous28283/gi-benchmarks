










namespace string {

template <typename T>
size_t duval(const T& s) {
    size_t n = s.size();
    size_t i = 0, ans = 0;
    while (i < n) {
        ans = i;
        size_t j = i + 1, k = i;
        while (j < (n + n) && s[j % n] >= s[k % n]) {
            if (s[k % n] < s[j % n]) {
                k = i;
            } else {
                k++;
            }
            j++;
        }
        while (i <= k) {
            i += j - k;
        }
    }
    return ans;

}

}


static void test() {
    using namespace string;


    std::string s1 = "abcab";
    assert(duval(s1) == 3);


    std::string s2 = "011100";
    assert(duval(s2) == 4);


    std::vector<int> v = {5, 2, 1, 3, 4};
    assert(duval(v) == 2);


    std::array<int, 5> a = {1, 2, 3, 4, 5};
    assert(duval(a) == 0);


    std::deque<char> d = {'a', 'z', 'c', 'a', 'b'};
    assert(duval(d) == 3);


    std::string s3;
    assert(duval(s3) == 0);


    std::vector<int> v2 = {5, 2, 1, 3, -4};
    assert(duval(v2) == 4);

    std::cout << "All tests passed!" << std::endl;
}


int main() {
    test();
    return 0;
}
