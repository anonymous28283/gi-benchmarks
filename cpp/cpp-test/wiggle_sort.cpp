









namespace sorting {

namespace wiggle_sort {


template <typename T>

std::vector<T> wiggleSort(const std::vector<T> &arr) {
    uint32_t size = arr.size();

    std::vector<T> out(
        arr);


    for (int i = 0; i < size; i += 2) {
        if (i > 0 && out[i - 1] > out[i]) {
            std::swap(out[i], out[i - 1]);
        }

        if (i < size - 1 && out[i] < out[i + 1]) {
            std::swap(out[i], out[i + 1]);
        }
    }

    return out;
}
}
}


template <typename T>
static void displayElements(const std::vector<T> &arr) {
    uint32_t size = arr.size();

    std::cout << "Sorted elements are as follows: ";

    std::cout << "[";

    for (int i = 0; i < size; i++) {
        std::cout << arr[i];
        if (i != size - 1) {
            std::cout << ", ";
        }
    }

    std::cout << "]" << std::endl;
}


static void test() {
    std::srand(std::time(nullptr));

    std::vector<float> data1(100);
    for (auto &d : data1) {
        d = float(std::rand() % 1000 - 500) / 100.f;
    }

    std::vector<float> sorted = sorting::wiggle_sort::wiggleSort<float>(data1);

    displayElements(sorted);

    for (uint32_t j = 0; j < data1.size(); j += 2) {
        assert(data1[j] <= data1[j + 1] &&
               data1[j + 1] >= data1[j + 2]);
    }

    std::cout << "Test 1 passed\n";
}


int main() {
    test();
    return 0;
}


