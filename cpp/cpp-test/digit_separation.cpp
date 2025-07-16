









namespace greedy_algorithms {


class DigitSeparation {
 public:

    DigitSeparation() {}


    std::vector<std::int64_t> digitSeparationReverseOrder(
        std::int64_t largeNumber) const {
        std::vector<std::int64_t> result;
        if (largeNumber != 0) {
            while (largeNumber != 0) {
                result.push_back(std::abs(largeNumber % 10));
                largeNumber /= 10;
            }
        } else {
            result.push_back(0);
        }
        return result;
    }


    std::vector<std::int64_t> digitSeparationForwardOrder(
        std::int64_t largeNumber) const {
        std::vector<std::int64_t> result =
            digitSeparationReverseOrder(largeNumber);
        std::reverse(result.begin(), result.end());
        return result;
    }
};

}


static void tests() {
    greedy_algorithms::DigitSeparation ds;


    std::int64_t number = 1234567890;
    std::vector<std::int64_t> expectedReverse = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<std::int64_t> expectedForward = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    std::vector<std::int64_t> reverseOrder =
        ds.digitSeparationReverseOrder(number);
    assert(reverseOrder == expectedReverse);
    std::vector<std::int64_t> forwardOrder =
        ds.digitSeparationForwardOrder(number);
    assert(forwardOrder == expectedForward);


    number = 5;
    expectedReverse = {5};
    expectedForward = {5};
    reverseOrder = ds.digitSeparationReverseOrder(number);
    assert(reverseOrder == expectedReverse);
    forwardOrder = ds.digitSeparationForwardOrder(number);
    assert(forwardOrder == expectedForward);


    number = 0;
    expectedReverse = {0};
    expectedForward = {0};
    reverseOrder = ds.digitSeparationReverseOrder(number);
    assert(reverseOrder == expectedReverse);
    forwardOrder = ds.digitSeparationForwardOrder(number);
    assert(forwardOrder == expectedForward);


    number = 987654321012345;
    expectedReverse = {5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    expectedForward = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5};
    reverseOrder = ds.digitSeparationReverseOrder(number);
    assert(reverseOrder == expectedReverse);
    forwardOrder = ds.digitSeparationForwardOrder(number);
    assert(forwardOrder == expectedForward);


    number = -987654321012345;
    expectedReverse = {5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    expectedForward = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5};
    reverseOrder = ds.digitSeparationReverseOrder(number);
    assert(reverseOrder == expectedReverse);
    forwardOrder = ds.digitSeparationForwardOrder(number);
    assert(forwardOrder == expectedForward);
}


int main() {
    tests();

    return 0;
}
