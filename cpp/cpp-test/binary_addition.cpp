







namespace greedy_algorithms {

class BinaryAddition {
 public:

    std::string addBinary(const std::string& a, const std::string& b) {
        if (!isValidBinaryString(a) || !isValidBinaryString(b)) {
            return "";

        }

        std::string result;
        int carry = 0;
        int maxLength = std::max(a.size(), b.size());


        for (int i = 0; i < maxLength; ++i) {

            int bitA = (i < a.size()) ? (a[a.size() - 1 - i] - '0') : 0;
            int bitB = (i < b.size()) ? (b[b.size() - 1 - i] - '0') : 0;


            int sum = bitA + bitB + carry;
            carry = sum / 2;
            result.push_back((sum % 2) +
                             '0');
        }
        if (carry) {
            result.push_back('1');
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

 private:

    bool isValidBinaryString(const std::string& str) const {
        return std::all_of(str.begin(), str.end(),
                           [](char c) { return c == '0' || c == '1'; });
    }
};
}


static void tests() {
    greedy_algorithms::BinaryAddition binaryAddition;


    assert(binaryAddition.addBinary("1010", "1101") == "10111");
    assert(binaryAddition.addBinary("1111", "1111") == "11110");
    assert(binaryAddition.addBinary("101", "11") == "1000");
    assert(binaryAddition.addBinary("0", "0") == "0");
    assert(binaryAddition.addBinary("1111", "1111") == "11110");
    assert(binaryAddition.addBinary("0", "10101") == "10101");
    assert(binaryAddition.addBinary("10101", "0") == "10101");
    assert(binaryAddition.addBinary("101010101010101010101010101010",
                                    "110110110110110110110110110110") ==
           "1100001100001100001100001100000");
    assert(binaryAddition.addBinary("1", "11111111") == "100000000");
    assert(binaryAddition.addBinary("10101010", "01010101") == "11111111");


    assert(binaryAddition.addBinary("10102", "1101") == "");
    assert(binaryAddition.addBinary("ABC", "1101") == "");
    assert(binaryAddition.addBinary("1010", "1102") == "");
    assert(binaryAddition.addBinary("111", "1x1") == "");
    assert(binaryAddition.addBinary("1x1", "111") == "");
    assert(binaryAddition.addBinary("1234", "1101") == "");
}


int main() {
    tests();
    return 0;
}
