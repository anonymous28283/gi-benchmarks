








namespace dynamic_programming {


namespace palindrome_partitioning {


int pal_part(const std::string &str) {
    int n = str.size();


    std::vector<std::vector<int> > cuts(n, std::vector<int>(n, 0));


    std::vector<std::vector<bool> > is_palindrome(n,
                                                  std::vector<bool>(n, false));


    for (int i = 0; i < n; i++) {
        is_palindrome[i][i] = true;
        cuts[i][i] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int start_index = 0; start_index < n - len + 1; start_index++) {
            int end_index = start_index + len - 1;

            if (len == 2) {
                is_palindrome[start_index][end_index] =
                    (str[start_index] == str[end_index]);
            } else {
                is_palindrome[start_index][end_index] =
                    (str[start_index] == str[end_index]) &&
                    is_palindrome[start_index + 1][end_index - 1];
            }

            if (is_palindrome[start_index][end_index]) {
                cuts[start_index][end_index] = 0;
            } else {
                cuts[start_index][end_index] = INT_MAX;
                for (int partition = start_index; partition <= end_index - 1;
                     partition++) {
                    cuts[start_index][end_index] =
                        std::min(cuts[start_index][end_index],
                                 cuts[start_index][partition] +
                                     cuts[partition + 1][end_index] + 1);
                }
            }
        }
    }

    return cuts[0][n - 1];
}
}
}


static void test() {

    std::vector<std::string> custom_input{"nitik", "ababbbabbababa", "abdc"};


    std::vector<int> calculated_output(3);

    for (int i = 0; i < 3; i++) {
        calculated_output[i] =
            dynamic_programming::palindrome_partitioning::pal_part(
                custom_input[i]);
    }


    std::vector<int> expected_output{2, 3, 3};




    for (int i = 0; i < 3; i++) {
        assert(expected_output[i] == calculated_output[i]);
    }

    std::cout << "All tests passed successfully!\n";
}


int main() {
    test();
    return 0;
}
