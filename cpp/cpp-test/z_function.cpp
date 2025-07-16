












std::vector<uint64_t> Z_function(const std::string &pattern) {
    uint64_t pattern_length = pattern.size();
    std::vector<uint64_t> z(pattern_length, 0);

    for (uint64_t i = 1, l = 0, r = 0; i < pattern_length; i++) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < pattern_length &&
               pattern[z[i]] == pattern[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
        }
    }
    return z;
}


std::vector<uint64_t> find_pat_in_text(const std::string &pattern,
                                       const std::string &text) {
    uint64_t text_length = text.size(), pattern_length = pattern.size();
    std::vector<uint64_t> z = Z_function(pattern + '#' + text);
    std::vector<uint64_t> matching_indexes;

    for (uint64_t i = 0; i < text_length; i++) {
        if (z[i + pattern_length + 1] == pattern_length) {
            matching_indexes.push_back(i);
        }
    }
    return matching_indexes;
}


static void test() {

    std::string text1 = "alskfjaldsabc1abc1abcbksbcdnsdabcabc";
    std::string pattern1 = "abc";


    std::vector<uint64_t> matching_indexes1 = find_pat_in_text(pattern1, text1);
    assert((matching_indexes1 == std::vector<uint64_t>{10, 14, 18, 30, 33}));


    std::string text2 = "greengrass";
    std::string pattern2 = "abc";


    std::vector<uint64_t> matching_indexes2 = find_pat_in_text(pattern2, text2);
    assert((matching_indexes2 == std::vector<uint64_t>{}));


    std::string text3 = "";
    std::string pattern3 = "abc";


    std::vector<uint64_t> matching_indexes3 = find_pat_in_text(pattern3, text3);
    assert((matching_indexes3 == std::vector<uint64_t>{}));


    std::string text4 = "redsand";
    std::string pattern4 = "";


    std::vector<uint64_t> matching_indexes4 = find_pat_in_text(pattern4, text4);
    assert((matching_indexes4 == std::vector<uint64_t>{0, 1, 2, 3, 4, 5, 6}));
}


int main() {
    test();
    return 0;
}
