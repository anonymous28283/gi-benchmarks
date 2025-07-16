






namespace {

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        out << arr[i];
        if (i < arr.size() - 1) {
            out << ", ";
        }
    }
    return out;
}

}


namespace sorting {
namespace {


template <typename T>
void partition3(std::vector<T> *arr, int32_t low, int32_t high, int32_t *i,
                int32_t *j) {

    if (high - low <= 1) {
        if ((*arr)[high] < (*arr)[low]) {
            std::swap((*arr)[high], (*arr)[low]);
        }
        *i = low;
        *j = high;
        return;
    }

    int32_t mid = low;
    T pivot = (*arr)[high];
    while (mid <= high) {
        if ((*arr)[mid] < pivot) {
            std::swap((*arr)[low++], (*arr)[mid++]);
        } else if ((*arr)[mid] == pivot) {
            mid++;
        } else if ((*arr)[mid] > pivot) {
            std::swap((*arr)[mid], (*arr)[high--]);
        }
    }


    *i = low - 1;
    *j = mid;
}
}


template <typename T>
void quicksort(std::vector<T> *arr, int32_t low, int32_t high) {
    if (low >= high) {
        return;
    }

    int32_t i = 0, j = 0;


    partition3(arr, low, high, &i, &j);


    quicksort(arr, low, i);
    quicksort(arr, j, high);
}


template <typename T>
std::vector<T> quicksort(std::vector<T> arr, int32_t low, int32_t high) {
    if (low >= high) {
        return arr;
    }

    int32_t i = 0, j = 0;


    partition3(&arr, low, high, &i, &j);


    quicksort(&arr, low, i);
    quicksort(&arr, j, high);

    return arr;
}
}


static void test_int() {
    std::cout << "\nTesting integer type arrays\n";

    for (int num_tests = 1; num_tests < 21; num_tests++) {
        size_t size = std::rand() % 500;
        std::vector<int> arr(size);
        for (auto &a : arr) {
            a = std::rand() % 500 - 250;
        }

        std::cout << "Test " << num_tests << "\t Array size:" << size << "\t ";
        std::vector<int> sorted = sorting::quicksort(arr, 0, int32_t(size) - 1);
        if (size < 20) {
            std::cout << "\t Sorted Array is:\n\t";
            std::cout << sorted << "\n";
        }
        assert(std::is_sorted(std::begin(sorted), std::end(sorted)));
        std::cout << "\t Passed\n";
    }
}


static void test_double() {
    std::cout << "\nTesting Double type arrays\n";
    for (int num_tests = 1; num_tests < 21; num_tests++) {
        size_t size = std::rand() % 500;
        std::vector<double> arr(size);
        for (auto &a : arr) {
            a = double(std::rand() % 500) -
                250.f;
            a /= 100.f;
        }

        std::cout << "Test " << num_tests << "\t Array size:" << size << "\t ";
        std::vector<double> sorted =
            sorting::quicksort(arr, 0, int32_t(size) - 1);
        if (size < 20) {
            std::cout << "\t Sorted Array is:\n\t";
            std::cout << sorted << "\n";
        }
        assert(std::is_sorted(std::begin(sorted), std::end(sorted)));
        std::cout << "\t Passed\n";
    }
}


int main() {
    std::srand(std::time(nullptr));
    test_int();
    test_double();
    return 0;
}
