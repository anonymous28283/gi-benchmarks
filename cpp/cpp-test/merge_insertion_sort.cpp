








namespace sorting {

namespace merge_insertion {


template <typename T, size_t N>
static void InsertionSort(std::array<T, N> *A, size_t start, size_t end) {
    size_t i = 0, j = 0;
    T *ptr = A->data();

    for (i = start; i < end; i++) {
        T temp = ptr[i];
        j = i;
        while (j > start && temp < ptr[j - 1]) {
            ptr[j] = ptr[j - 1];
            j--;
        }




        ptr[j] = temp;
    }
}


template <typename T, size_t N>
static void merge(std::array<T, N> *array, size_t min, size_t max, size_t mid) {
    size_t firstIndex = min;
    size_t secondIndex = mid + 1;

    auto ptr = array->data();
    std::array<T, N + 1> tempArray{0};


    for (size_t index = min; index <= max; index++) {

        if (firstIndex <= mid &&
            (secondIndex > max || ptr[firstIndex] <= ptr[secondIndex])) {
            tempArray[index] = ptr[firstIndex];
            firstIndex++;
        } else {
            tempArray[index] = ptr[secondIndex];
            secondIndex++;
        }
    }


    memcpy(ptr + min, tempArray.data() + min, (max - min) * sizeof(T));


}


template <typename T, size_t N>
void mergeSort(std::array<T, N> *array, size_t min, size_t max,
               size_t threshold) {

    if ((max - min) <= threshold) {
        InsertionSort(array, min, max);
    } else {

        size_t mid = (max + min) >> 1;


        mergeSort(array, min, mid, threshold);
        mergeSort(array, mid, max, threshold);


        merge(array, min, max, mid);
    }
}

}
}


static void test() {
    constexpr size_t size = 30;
    std::array<int, size> array{0};

    for (int i = 0; i < size; i++) {
        array[i] = std::rand() % 100 - 50;
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    sorting::merge_insertion::InsertionSort(&array, 0, size);



    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    assert(std::is_sorted(std::begin(array), std::end(array)));
    std::cout << "Test passed\n";
}


int main() {
    std::srand(std::time(nullptr));
    test();
    return 0;
}
