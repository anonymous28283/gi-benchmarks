







namespace string_search {

std::vector<size_t> getFailureArray(const std::string &pattern) {
    size_t pattern_length = pattern.size();
    std::vector<size_t> failure(pattern_length + 1);
    failure[0] = std::string::npos;
    size_t j = std::string::npos;
    for (int i = 0; i < pattern_length; i++) {
        while (j != std::string::npos && pattern[j] != pattern[i]) {
            j = failure[j];
        }
        failure[i + 1] = ++j;
    }
    return failure;
}


size_t kmp(const std::string &pattern, const std::string &text) {
    if (pattern.empty()) {
        return 0;
    }
    std::vector<size_t> failure = getFailureArray(pattern);
    size_t text_length = text.size();
    size_t pattern_length = pattern.size();
    size_t k = 0;
    for (size_t j = 0; j < text_length; j++) {
        while (k != std::string::npos && pattern[k] != text[j]) {
            k = failure[k];
        }
        if (++k == pattern_length) {
            return j - k + 1;
        }
    }
    return std::string::npos;
}
}

using string_search::kmp;


static void tests() {
    assert(kmp("abc1abc12l", "alskfjaldsabc1abc1abc12k2") == std::string::npos);
    assert(kmp("bca", "abcabc") == 1);
    assert(kmp("World", "helloWorld") == 5);
    assert(kmp("c++", "his_is_c++") == 7);
    assert(kmp("happy", "happy_coding") == 0);
    assert(kmp("", "pattern is empty") == 0);


    std::cout << "All KMP algorithm tests have successfully passed!\n";
}


int main() {
    tests();
    return 0;
}
