







void stoogeSort(std::vector<int>* L, size_t i, size_t j) {
    if (i >= j) {
        return;
    }
    if ((*L)[i] > (*L)[j]) {
        std::swap((*L)[i], (*L)[j]);
    }
    if (j - i > 1) {
        size_t third = (j - i + 1) / 3;
        stoogeSort(L, i, j - third);
        stoogeSort(L, i + third, j);
        stoogeSort(L, i, j - third);
    }
}


void test1() {
	std::vector<int> L = { 8, 9, 10, 4, 3, 5, 1 };
	stoogeSort(&L, 0, L.size() - 1);
	assert(std::is_sorted(std::begin(L), std::end(L)));
}


void test2() {
	std::vector<int> L = { -1 };
	stoogeSort(&L, 0, L.size() - 1);
	assert(std::is_sorted(std::begin(L), std::end(L)));
}


void test3() {
	std::vector<int> L = { 1, 2, 5, 4, 1, 5 };
	stoogeSort(&L, 0, L.size() - 1);
	assert(std::is_sorted(std::begin(L), std::end(L)));
}


int main() {
	test1();
	test2();
	test3();
    
    std::cout << "All tests have successfully passed!\n";
	return 0;
}
