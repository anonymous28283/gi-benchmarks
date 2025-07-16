








class Longest_Substring {
public:

    int lengthOfLongestSubstring(std::string s) {

        if (s.size() == 1) return 1;


        std::unordered_map<char, int> m;
        int n = s.length();


        std::deque<char> temp;
        std::deque<char> res;
        int i, j;


        for (i = 0, j = 0; i < n && j < n;) {
            m[s[j]]++;


            if (m[s[j]] > 1) {
                if (temp.size() > res.size()) {
                    res = temp;
                }

                while (m[s[j]] > 1) {
                    temp.pop_front();
                    m[s[i]]--;
                    i++;
                }
            }


            temp.push_back(s[j]);
            j++;
        }


        if (temp.size() > res.size()) {
            res = temp;
        }

        return res.size();
    }
};


static void tests() {
    Longest_Substring soln;
    assert(soln.lengthOfLongestSubstring("abcabcbb") == 3);
    assert(soln.lengthOfLongestSubstring("bbbbb") == 1);
    assert(soln.lengthOfLongestSubstring("pwwkew") == 3);
    assert(soln.lengthOfLongestSubstring("") == 0);
    assert(soln.lengthOfLongestSubstring("abcdef") == 6);
    assert(soln.lengthOfLongestSubstring("a") == 1);
    std::cout << "All test cases passed!" << std::endl;
}


int main() {
    tests();
    return 0;
}
