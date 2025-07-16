








template <typename T>
std::uint32_t longest_increasing_subsequence_using_binary_search(std::vector<T>& nums) {
    if (nums.empty()) return 0;

    std::vector<T> ans;
    ans.push_back(nums[0]);
    for (std::size_t i = 1; i < nums.size(); i++) {
        if (nums[i] > ans.back()) {
            ans.push_back(nums[i]);
        } else {
            auto idx = std::lower_bound(ans.begin(), ans.end(), nums[i]) - ans.begin();
            ans[idx] = nums[i];
        }
    }
    return static_cast<std::uint32_t>(ans.size());
}


static void tests() {
    std::vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};
    assert(longest_increasing_subsequence_using_binary_search(arr) == 4);

    std::vector<int> arr2 = {0, 1, 0, 3, 2, 3};
    assert(longest_increasing_subsequence_using_binary_search(arr2) == 4);

    std::vector<int> arr3 = {7, 7, 7, 7, 7, 7, 7};
    assert(longest_increasing_subsequence_using_binary_search(arr3) == 1);

    std::vector<int> arr4 = {-10, -1, -5, 0, 5, 1, 2};
    assert(longest_increasing_subsequence_using_binary_search(arr4) == 5);

    std::vector<double> arr5 = {3.5, 1.2, 2.8, 3.1, 4.0};
    assert(longest_increasing_subsequence_using_binary_search(arr5) == 4);

    std::vector<char> arr6 = {'a', 'b', 'c', 'a', 'd'};
    assert(longest_increasing_subsequence_using_binary_search(arr6) == 4);

    std::vector<int> arr7 = {};
    assert(longest_increasing_subsequence_using_binary_search(arr7) == 0);

    std::cout << "All tests have successfully passed!\n";
}


int main() {
    tests();
    return 0;
}
