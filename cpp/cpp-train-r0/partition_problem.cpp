






namespace dp {


namespace partitionProblem {


bool findPartiion(const std::vector<uint64_t> &arr, uint64_t size) {
    uint64_t sum = std::accumulate(arr.begin(), arr.end(),
                                   0);

    if (sum % 2 != 0) {
        return false;
    }
    std::vector<bool> part;



    for (uint64_t it = 0; it <= sum / 2; ++it) {
        part.push_back(false);
    }


    for (uint64_t it = 0; it < size; ++it) {

        for (uint64_t it2 = sum / 2; it2 >= arr[it];
             --it2) {

            if (part[it2 - arr[it]] == 1 || it2 == arr[it]) {
                part[it2] = true;
            }
        }
    }
    return part[sum / 2];
}
}
}


static void test() {
    std::vector<uint64_t> arr = {{1, 3, 3, 2, 3, 2}};
    uint64_t n = arr.size();
    bool expected_result = true;
    bool derived_result = dp::partitionProblem::findPartiion(arr, n);
    std::cout << "1st test: ";
    assert(expected_result == derived_result);
    std::cout << "Passed!" << std::endl;
}


int main() {
    test();
    return 0;
}
