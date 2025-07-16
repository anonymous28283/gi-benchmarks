












namespace strings {

namespace manacher {

std::string manacher(const std::string &prototype) {
    if (prototype.size() > 0) {


        std::string stuffed_string = "";
        for (auto str : prototype) {
            stuffed_string += str;
            stuffed_string += "#";
        }
        stuffed_string = "@#" + stuffed_string + "&";

        std::vector<uint64_t> palindrome_max_half_length(
            stuffed_string.size(),
            0);




        uint64_t bigger_center =
            0;



        uint64_t right = 0;




        for (uint64_t i = 1; i < stuffed_string.size() - 1; i++) {
            if (i < right) {

                uint64_t opposite_to_i =
                    2 * bigger_center -
                    i;






                palindrome_max_half_length[i] = std::min(
                    palindrome_max_half_length[opposite_to_i], right - i);
            }



            while (stuffed_string[i + (palindrome_max_half_length[i] + 1)] ==
                   stuffed_string[i - (palindrome_max_half_length[i] + 1)]) {
                palindrome_max_half_length[i]++;
            }





            if (i + palindrome_max_half_length[i] > right) {
                bigger_center = i;
                right = i + palindrome_max_half_length[i];
            }
        }


        uint64_t half_length = 0;
        uint64_t center_index = 0;

        for (uint64_t i = 1; i < stuffed_string.size() - 1; i++) {
            if (palindrome_max_half_length[i] > half_length) {
                half_length = palindrome_max_half_length[i];
                center_index = i;
            }
        }

        std::string palindromic_substring =
            "";

        if (half_length > 0) {




            uint64_t start =
                center_index - half_length +
                1;
            uint64_t end =
                center_index + half_length -
                1;
            for (uint64_t index = start; index <= end; index += 2) {
                palindromic_substring += stuffed_string[index];
            }
        } else {



            palindromic_substring = prototype[0];
        }
        return palindromic_substring;

    } else {

        return "";
    }
}

}
}


static void test() {
    assert(strings::manacher::manacher("") == "");
    assert(strings::manacher::manacher("abababc") == "ababa");
    assert(strings::manacher::manacher("cbaabd") == "baab");
    assert(strings::manacher::manacher("DedzefDeD") == "DeD");
    assert(strings::manacher::manacher("XZYYXXYZXX") == "YXXY");
    assert(strings::manacher::manacher("1sm222m10abc") == "m222m");
    assert(strings::manacher::manacher("798989591") == "98989");
    assert(strings::manacher::manacher("xacdedcax") == "xacdedcax");
    assert(strings::manacher::manacher("xaccax") == "xaccax");
    assert(strings::manacher::manacher("a") == "a");
    assert(strings::manacher::manacher("xy") == "x");
    assert(strings::manacher::manacher("abced") == "a");

    std::cout << "All tests have passed!" << std::endl;
}


int main() {
    test();
    return 0;
}
