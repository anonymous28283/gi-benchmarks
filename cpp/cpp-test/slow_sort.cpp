











void SlowSort(int a[], int i, int j) {
    if (i >= j)
        return;
    int m = i + (j - i) / 2;

    int temp;
    SlowSort(a, i, m);
    SlowSort(a, m + 1, j);
    if (a[j] < a[m]) {
        temp = a[j];
        a[j] = a[m];
        a[m] = temp;
    }
    SlowSort(a, i, j - 1);
}



int main() {
    int size;
    std::cout << "\nEnter the number of elements : ";

    std::cin >> size;

    int *arr = new int[size];

    std::cout << "\nEnter the unsorted elements : ";

    for (int i = 0; i < size; ++i) {
        std::cout << "\n";
        std::cin >> arr[i];
    }

    SlowSort(arr, 0, size);

    std::cout << "Sorted array\n";

    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }

    delete[] arr;
    return 0;
}
