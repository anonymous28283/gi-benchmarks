







namespace dynamic_programming {

namespace abbreviation {

bool abbreviation_recursion(std::vector<std::vector<bool>> *memo,
                            std::vector<std::vector<bool>> *visited,
                            const std::string &str, const std::string &result,
                            uint32_t str_idx = 0, uint32_t result_idx = 0) {
    bool ans = memo->at(str_idx).at(result_idx);
    if (str_idx == str.size() && result_idx == result.size()) {
        return true;
    } else if (str_idx == str.size() && result_idx != result.size()) {

        return false;
    } else if (!visited->at(str_idx).at(result_idx)) {

        if (str[str_idx] == result[result_idx]) {
            ans = abbreviation_recursion(memo, visited, str, result,
                                         str_idx + 1, result_idx + 1);
        } else if (str[str_idx] - 32 == result[result_idx]) {
            ans = abbreviation_recursion(memo, visited, str, result,
                                         str_idx + 1, result_idx + 1) ||
                  abbreviation_recursion(memo, visited, str, result,
                                         str_idx + 1, result_idx);
        } else {




            if (str[str_idx] >= 'A' && str[str_idx] <= 'Z') {
                ans = false;
            } else {
                ans = abbreviation_recursion(memo, visited, str, result,
                                             str_idx + 1, result_idx);
            }
        }
    }
    (*memo)[str_idx][result_idx] = ans;
    (*visited)[str_idx][result_idx] = true;
    return (*memo)[str_idx][result_idx];
}

bool abbreviation(const std::string &str, const std::string &result) {
    std::vector<std::vector<bool>> memo(
        str.size() + 1, std::vector<bool>(result.size() + 1, false));

    for (uint32_t i = 0; i <= str.size(); ++i) {
        memo[i][0] = true;
    }
    for (uint32_t i = 1; i <= result.size(); ++i) {
        memo[0][i] = false;
    }
    for (uint32_t i = 1; i <= str.size(); ++i) {
        for (uint32_t j = 1; j <= result.size(); ++j) {
            if (str[i - 1] == result[j - 1]) {
                memo[i][j] = memo[i - 1][j - 1];
            } else if (str[i - 1] - 32 == result[j - 1]) {
                memo[i][j] = (memo[i - 1][j - 1] || memo[i - 1][j]);
            } else {
                if (str[i - 1] >= 'A' && str[i - 1] <= 'Z') {
                    memo[i][j] = false;
                } else {
                    memo[i][j] = memo[i - 1][j];
                }
            }
        }
    }
    return memo.back().back();
}
}
}


static void test() {
    std::string s = "daBcd", t = "ABC";
    std::vector<std::vector<bool>> memo(s.size() + 1,
                                        std::vector<bool>(t.size() + 1, false)),
        visited(s.size() + 1, std::vector<bool>(t.size() + 1, false));

    assert(dynamic_programming::abbreviation::abbreviation_recursion(
               &memo, &visited, s, t) == true);
    assert(dynamic_programming::abbreviation::abbreviation(s, t) == true);
    s = "XXVVnDEFYgYeMXzWINQYHAQKKOZEYgSRCzLZAmUYGUGILjMDET";
    t = "XXVVDEFYYMXWINQYHAQKKOZEYSRCLZAUYGUGILMDETQVWU";
    memo = std::vector<std::vector<bool>>(
        s.size() + 1, std::vector<bool>(t.size() + 1, false));

    visited = std::vector<std::vector<bool>>(
        s.size() + 1, std::vector<bool>(t.size() + 1, false));

    assert(dynamic_programming::abbreviation::abbreviation_recursion(
               &memo, &visited, s, t) == false);
    assert(dynamic_programming::abbreviation::abbreviation(s, t) == false);

    s = "DRFNLZZVHLPZWIupjwdmqafmgkg";
    t = "DRFNLZZVHLPZWI";

    memo = std::vector<std::vector<bool>>(
        s.size() + 1, std::vector<bool>(t.size() + 1, false));

    visited = std::vector<std::vector<bool>>(
        s.size() + 1, std::vector<bool>(t.size() + 1, false));

    assert(dynamic_programming::abbreviation::abbreviation_recursion(
               &memo, &visited, s, t) == true);
    assert(dynamic_programming::abbreviation::abbreviation(s, t) == true);
}


int main() {
    test();
    return 0;
}
