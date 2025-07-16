






namespace dynamic_programming {

std::string lps(const std::string& a) {
    const auto b = std::string(a.rbegin(), a.rend());
    const auto m = a.length();
    using ind_type = std::string::size_type;
    std::vector<std::vector<ind_type> > res(m + 1,
                                            std::vector<ind_type>(m + 1));




    for (ind_type i = 0; i <= m; i++) {
        for (ind_type j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                res[i][j] = 0;
            } else if (a[i - 1] == b[j - 1]) {
                res[i][j] = res[i - 1][j - 1] + 1;
            } else {
                res[i][j] = std::max(res[i - 1][j], res[i][j - 1]);
            }
        }
    }

    auto idx = res[m][m];

    std::string ans(idx, '\0');
    ind_type i = m, j = m;



    while (i > 0 && j > 0) {


        if (a[i - 1] == b[j - 1]) {
            ans[idx - 1] = a[i - 1];
            i--;
            j--;
            idx--;
        }


        else if (res[i - 1][j] > res[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return ans;
}
}


static void test() {
    assert(dynamic_programming::lps("radar") == "radar");
    assert(dynamic_programming::lps("abbcbaa") == "abcba");
    assert(dynamic_programming::lps("bbbab") == "bbbb");
    assert(dynamic_programming::lps("") == "");
}


int main() {
    test();
    return 0;
}
