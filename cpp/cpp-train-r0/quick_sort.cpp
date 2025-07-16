









namespace sorting {

namespace quick_sort {

template <typename T>
int partition(std::vector<T> *arr, const int &low, const int &high) {
    T pivot = (*arr)[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {


        if ((*arr)[j] <= pivot) {
            i++;
            std::swap((*arr)[i], (*arr)[j]);
        }
    }

    std::swap((*arr)[i + 1], (*arr)[high]);
    return (i + 1);
}


template <typename T>
void quick_sort(std::vector<T> *arr, const int &low, const int &high) {
    if (low < high) {
        int p = partition(arr, low, high);

        quick_sort(arr, low, p - 1);
        quick_sort(arr, p + 1, high);
    }
}


template <typename T>
std::vector<T> quick_sort(std::vector<T> arr, const int &low, const int &high) {
    if (low < high) {
        int p = partition(&arr, low, high);

        quick_sort(&arr, low, p - 1);
        quick_sort(&arr, p + 1, high);
    }
    return arr;
}


template <typename T>
void show(const std::vector<T> &arr, const int &size) {
    for (int i = 0; i < size; i++) std::cout << arr[i] << " ";
    std::cout << "\n";
}

}
}


static void tests() {

    std::vector<uint64_t> arr = {5, 3, 8, 12, 14, 16, 28, 96, 2, 5977};
    std::vector<uint64_t> arr_sorted = sorting::quick_sort::quick_sort(
        arr, 0, int(std::end(arr) - std::begin(arr)) - 1);

    assert(std::is_sorted(std::begin(arr_sorted), std::end(arr_sorted)));
    std::cout << "\n1st test: passed!\n";


    std::vector<int64_t> arr2 = {9,    15,   28,   96,  500, -4, -58,
                                 -977, -238, -800, -21, -53, -55};
    std::vector<int64_t> arr_sorted2 = sorting::quick_sort::quick_sort(
        arr2, 0, std::end(arr2) - std::begin(arr2));

    assert(std::is_sorted(std::begin(arr_sorted2), std::end(arr_sorted2)));
    std::cout << "2nd test: passed!\n";


    std::vector<double> arr3 = {29,  36,   1100, 0,      77,     1,
                                6.7, 8.97, 1.74, 950.10, -329.65};
    std::vector<double> arr_sorted3 = sorting::quick_sort::quick_sort(
        arr3, 0, int(std::end(arr3) - std::begin(arr3)) - 1);

    assert(std::is_sorted(std::begin(arr_sorted3), std::end(arr_sorted3)));
    std::cout << "3rd test: passed!\n";


    size_t size = std::rand() % 750 + 100;

    std::vector<float> arr4(size);
    for (uint64_t i = 0; i < size; i++) {
        arr4[i] = static_cast<float>(std::rand()) /
                      static_cast<float>(RAND_MAX / 999.99 - 0.99) -
                  250;
    }

    std::vector<float> arr4_sorted = sorting::quick_sort::quick_sort(
        arr4, 0, int(std::end(arr4) - std::begin(arr4)) - 1);
    assert(std::is_sorted(std::begin(arr4_sorted), std::end(arr4_sorted)));

    std::cout << "4th test: passed!\n";


    std::cout << "\n\tPrinting all sorted arrays:\t\n";

    std::cout << "1st array:\n";
    sorting::quick_sort::show(arr_sorted, std::end(arr) - std::begin(arr));
    std::cout << std::endl;
    std::cout << "2nd array:\n";
    sorting::quick_sort::show(arr_sorted2, std::end(arr2) - std::begin(arr2));
    std::cout << std::endl;
    std::cout << "3rd array:\n";
    sorting::quick_sort::show(arr_sorted3,
                              int(std::end(arr3) - std::begin(arr3)) - 1);
    std::cout << std::endl;
    std::cout << "Start: 4th array:\n\n";
    sorting::quick_sort::show(
        arr4_sorted, int(std::end(arr4_sorted) - std::begin(arr4_sorted)) - 1);
    std::cout << "\nEnd: 4th array.\n";
}


int main() {
    int choice = 0;

    std::cout << "\tAvailable modes\t\n\n";
    std::cout << "1. Self-tests mode\n2. Interactive mode";

    std::cout << "\nChoose a mode: ";
    std::cin >> choice;
    std::cout << "\n";

    while ((choice != 1) && (choice != 2)) {
        std::cout << "Invalid option. Choose between the valid modes: ";
        std::cin >> choice;
    }

    if (choice == 1) {
        std::srand(std::time(nullptr));
        tests();
    } else if (choice == 2) {
        int size = 0;
        std::cout << "\nEnter the number of elements: ";

        std::cin >> size;
        std::vector<float> arr(size);

        std::cout
            << "\nEnter the unsorted elements (can be negative/decimal): ";

        for (int i = 0; i < size; ++i) {
            std::cout << "\n";
            std::cin >> arr[i];
        }
        sorting::quick_sort::quick_sort(&arr, 0, size - 1);
        std::cout << "\nSorted array: \n";
        sorting::quick_sort::show(arr, size);
    }
    return 0;
}
