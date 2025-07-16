








namespace dynamic_programming {



namespace minimum_edit_distance {


uint64_t min(uint64_t x, uint64_t y, uint64_t z) {
    if (x <= y && x <= z) {
        return x;
    }
    if (y <= x && y <= z) {
        return y;
    } else {
        return z;
    }
}


uint64_t editDistDP(std::string str1, std::string str2, uint64_t m,
                    uint64_t n) {

    std::vector<std::vector<uint64_t>> dp(
        m + 1,
        std::vector<uint64_t>(
            n +
            1));


    for (uint64_t i = 0; i <= m; i++) {
        for (uint64_t j = 0; j <= n; j++) {


            if (i == 0) {
                dp[i][j] = j;
            }



            else if (j == 0) {
                dp[i][j] = i;
            }



            else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }



            else {
                dp[i][j] = 1 + min(dp[i][j - 1],
                                   dp[i - 1][j],
                                   dp[i - 1][j - 1]);
            }
        }
    }

    return dp[m][n];

}
}
}


static void test() {

    std::string str1 = "INTENTION";
    std::string str2 = "EXECUTION";
    uint64_t expected_output1 = 5;
    uint64_t output1 = dynamic_programming::minimum_edit_distance::editDistDP(
        str1, str2, str1.length(),
        str2.length());

    assert(output1 ==
           expected_output1);
    std::cout << "Minimum Number of Operations Required: " << output1
              << std::endl;


    std::string str3 = "SATURDAY";
    std::string str4 = "SUNDAY";
    uint64_t expected_output2 = 3;
    uint64_t output2 = dynamic_programming::minimum_edit_distance::editDistDP(
        str3, str4, str3.length(), str4.length());
    assert(output2 == expected_output2);
    std::cout << "Minimum Number of Operations Required: " << output2
              << std::endl;
}


int main(int argc, char *argv[]) {
    test();
    return 0;
}
