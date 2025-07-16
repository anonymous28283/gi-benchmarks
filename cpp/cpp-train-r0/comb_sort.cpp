






int FindNextGap(int gap) {
    gap = (gap * 10) / 13;

    return std::max(1, gap);
}


void CombSort(int *arr, int l, int r) {

    int gap = r;


    bool swapped = true;


    while (gap != 1 || swapped) {

        gap = FindNextGap(gap);

        swapped = false;


        for (int i = l; i < r - gap; ++i) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

void tests() {

    int arr1[10] = {34, 56, 6, 23, 76, 34, 76, 343, 4, 76};
    CombSort(arr1, 0, 10);
    assert(std::is_sorted(arr1, arr1 + 10));
    std::cout << "Test 1 passed\n";


    int arr2[8] = {-6, 56, -45, 56, 0, -1, 8, 8};
    CombSort(arr2, 0, 8);
    assert(std::is_sorted(arr2, arr2 + 8));
    std::cout << "Test 2 Passed\n";
}


int main() {

    tests();


    int n;
    std::cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; ++i) std::cin >> arr[i];
    CombSort(arr, 0, n);
    for (int i = 0; i < n; ++i) std::cout << arr[i] << ' ';
    delete[] arr;
    return 0;
}
