









namespace sorting {

namespace random_pivot_quick_sort {

template <size_t T>
void showArray(std::array<int64_t, T> arr) {
    for (int64_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}


int64_t getRandomIndex(int64_t start, int64_t end) {
    srand(time(nullptr));
    int64_t randomPivotIndex = start + rand() % (end - start + 1);
    return randomPivotIndex;
}


template <size_t size>
std::tuple<int64_t, std::array<int64_t, size>> partition(
    std::array<int64_t, size> arr, int64_t start, int64_t end) {
    int64_t pivot = arr[end];

    int64_t pInd = start;

    for (int64_t i = start; i < end; i++) {
        if (arr[i] <= pivot) {
            std::swap(arr[i], arr[pInd]);

            pInd++;
        }
    }
    std::swap(arr[pInd],
              arr[end]);
    return std::make_tuple(pInd, arr);
}


template <size_t size>
std::array<int64_t, size> quickSortRP(std::array<int64_t, size> arr,
                                      int64_t start, int64_t end) {
    if (start < end) {
        int64_t randomIndex = getRandomIndex(start, end);


        std::swap(arr[end], arr[randomIndex]);

        int64_t pivotIndex = 0;

        std::tie(pivotIndex, arr) = partition(arr, start, end);


        std::array<int64_t, arr.size()> rightSortingLeft =
            quickSortRP(arr, start, pivotIndex - 1);
        std::array<int64_t, arr.size()> full_sorted =
            quickSortRP(rightSortingLeft, pivotIndex + 1, end);
        arr = full_sorted;
    }
    return arr;
}


template <size_t size>
std::array<int64_t, size> generateUnsortedArray(int64_t from, int64_t to) {
    srand(time(nullptr));
    std::array<int64_t, size> unsortedArray{};
    assert(from < to);
    int64_t i = 0;
    while (i < size) {
        int64_t randomNum = from + rand() % (to - from + 1);
        if (randomNum) {
            unsortedArray[i] = randomNum;
            i++;
        }
    }
    return unsortedArray;
}

}
}


class TestCases {
 private:

    template <typename T>
    void log(T msg) {

        std::cout << "[TESTS] : ---> " << msg << std::endl;
    }

 public:

    void runTests() {
        log("Running Tests...");

        testCase_1();
        testCase_2();
        testCase_3();

        log("Test Cases over!");
        std::cout << std::endl;
    }


    void testCase_1() {
        const int64_t inputSize = 1;
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("This is test case 1 for Random Pivot Quick Sort Algorithm : ");
        log("Description:");
        log("   EDGE CASE : Only contains one element");
        std::array<int64_t, inputSize> unsorted_arr{2};

        int64_t start = 0;
        int64_t end = unsorted_arr.size() - 1;

        log("Running algorithm of data of length 50 ...");
        std::array<int64_t, unsorted_arr.size()> sorted_arr =
            sorting::random_pivot_quick_sort::quickSortRP(unsorted_arr, start,
                                                          end);
        log("Algorithm finished!");

        log("Checking assert expression...");
        assert(std::is_sorted(sorted_arr.begin(), sorted_arr.end()));
        log("Assertion check passed!");

        log("[PASS] : TEST CASE 1 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }


    void testCase_2() {
        const int64_t inputSize = 500;
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("Description:");
        log("   BIG INPUT : Contains 500 elements and repeated elements");
        log("This is test case 2 for Random Pivot Quick Sort Algorithm : ");
        std::array<int64_t, inputSize> unsorted_arr =
            sorting::random_pivot_quick_sort::generateUnsortedArray<inputSize>(
                1, 10000);

        int64_t start = 0;
        int64_t end = unsorted_arr.size() - 1;

        log("Running algorithm of data of length 500 ...");
        std::array<int64_t, unsorted_arr.size()> sorted_arr =
            sorting::random_pivot_quick_sort::quickSortRP(unsorted_arr, start,
                                                          end);
        log("Algorithm finished!");

        log("Checking assert expression...");
        assert(std::is_sorted(sorted_arr.begin(), sorted_arr.end()));
        log("Assertion check passed!");

        log("[PASS] : TEST CASE 2 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }


    void testCase_3() {
        const int64_t inputSize = 1000;
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
        log("This is test case 3 for Random Pivot Quick Sort Algorithm : ");
        log("Description:");
        log("   LARGE INPUT : Contains 1000 elements and repeated elements");
        std::array<int64_t, inputSize> unsorted_arr =
            sorting::random_pivot_quick_sort::generateUnsortedArray<inputSize>(
                1, 10000);

        int64_t start = 0;
        int64_t end = unsorted_arr.size() - 1;

        log("Running algorithm...");
        std::array<int64_t, unsorted_arr.size()> sorted_arr =
            sorting::random_pivot_quick_sort::quickSortRP(unsorted_arr, start,
                                                          end);
        log("Algorithm finished!");

        log("Checking assert expression...");
        assert(std::is_sorted(sorted_arr.begin(), sorted_arr.end()));
        log("Assertion check passed!");

        log("[PASS] : TEST CASE 3 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
            "~");
    }
};


static void test() {
    TestCases tc = TestCases();
    tc.runTests();
}


int main(int argc, char *argv[]) {
    test();

    const int64_t inputSize = 10;
    std::array<int64_t, inputSize> unsorted_array =
        sorting::random_pivot_quick_sort::generateUnsortedArray<inputSize>(
            50, 1000);
    std::cout << "Unsorted array is : " << std::endl;
    sorting::random_pivot_quick_sort::showArray(unsorted_array);

    std::array<int64_t, inputSize> sorted_array =
        sorting::random_pivot_quick_sort::quickSortRP(
            unsorted_array, 0, unsorted_array.size() - 1);
    std::cout << "Sorted array is : " << std::endl;
    sorting::random_pivot_quick_sort::showArray(sorted_array);
    return 0;
}
