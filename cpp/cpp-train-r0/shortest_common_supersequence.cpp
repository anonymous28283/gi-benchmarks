









namespace dynamic_programming {


    namespace shortest_common_supersequence {
        

        std::string scs(const std::string &str1, const std::string &str2) {



            if(str1.empty() && str2.empty()) {
                return "";
            }
            else if(str1.empty()) {
                return str2;
            }
            else if(str2.empty()) {
                return str1;
            }


            std::vector <std::vector <int>> lookup(str1.length() + 1, std::vector <int> (str2.length() + 1, 0));
      
            for(int i=1; i <= str1.length(); i++) {
                for(int j=1; j <= str2.length(); j++) {
                    if(str1[i-1] == str2[j-1]) {
                        lookup[i][j] = lookup[i-1][j-1] + 1;
                    }
                    else {
                        lookup[i][j] = std::max(lookup[i-1][j], lookup[i][j-1]);
                    }
                }
            }




            int i=str1.length();
            int j=str2.length();
            std::string s;
      
            while(i>0 && j>0) {



                if(str1[i-1] == str2[j-1]) {
                    s.push_back(str1[i-1]);
                    i--;
                    j--;
                }

                else {
                    if(lookup[i-1][j] > lookup[i][j-1]) {
                        s.push_back(str1[i-1]);
                        i--;
                    }
                    else {
                        s.push_back(str2[j-1]);
                        j--;
                    }
                }
            }



            while(i > 0) {
                s.push_back(str1[i-1]);
                i--;
            }


            while(j > 0) {
                s.push_back(str2[j-1]);
                j--;
            }



            reverse(s.begin(), s.end());
            return s;
        }
    }
}


static void test() {

    std::vector <std::vector <std::string>> scsStrings {
        {"ABCXYZ", "ABZ"},
        {"ABZ", "ABCXYZ"},
        {"AGGTAB", "GXTXAYB"},
        {"X", "Y"},
    };


    std::vector <std::string> calculatedOutput(4, "");
    int i=0;
    for(auto & scsString : scsStrings) {
        
        calculatedOutput[i] = dynamic_programming::shortest_common_supersequence::scs(
            scsString[0], scsString[1]
        );
        i++;
    }


    std::vector <std::string> expectedOutput {
        "ABCXYZ",
        "ABCXYZ",
        "AGGXTXAYB",
        "XY"
    };




    for(int i=0; i < scsStrings.size(); i++) {
        assert(expectedOutput[i] == calculatedOutput[i]);
    }

    std::cout << "All tests passed successfully!\n";
    return;
}


int main() {

    test();


    std::string s1, s2;
    std::cin >> s1;
    std::cin >> s2;

    std::string ans;


    ans = dynamic_programming::shortest_common_supersequence::scs(s1, s2);
    std::cout << ans;
    return 0;
}
