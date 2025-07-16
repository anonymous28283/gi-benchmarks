










void CocktailSelectionSort(std::vector<int> *vec, int low, int high) {
    while (low <= high) {
        int minimum = (*vec)[low];
        int minimumindex = low;
        int maximum = (*vec)[high];
        int maximumindex = high;

        for (int i = low; i <= high; i++) {
            if ((*vec)[i] >= maximum) {
                maximum = (*vec)[i];
                maximumindex = i;
            }
            if ((*vec)[i] <= minimum) {
                minimum = (*vec)[i];
                minimumindex = i;
            }
        }
        if (low != maximumindex || high != minimumindex) {
            std::swap((*vec)[low], (*vec)[minimumindex]);
            std::swap((*vec)[high], (*vec)[maximumindex]);
        } else {
            std::swap((*vec)[low], (*vec)[high]);
        }

        low++;
        high--;
    }
}



void CocktailSelectionSort_v2(std::vector<int> *vec, int low, int high) {
    if (low >= high)
        return;

    int minimum = (*vec)[low];
    int minimumindex = low;
    int maximum = (*vec)[high];
    int maximumindex = high;

    for (int i = low; i <= high; i++) {
        if ((*vec)[i] >= maximum) {
            maximum = (*vec)[i];
            maximumindex = i;
        }
        if ((*vec)[i] <= minimum) {
            minimum = (*vec)[i];
            minimumindex = i;
        }
    }
    if (low != maximumindex || high != minimumindex) {
        std::swap((*vec)[low], (*vec)[minimumindex]);
        std::swap((*vec)[high], (*vec)[maximumindex]);
    } else {
        std::swap((*vec)[low], (*vec)[high]);
    }

    CocktailSelectionSort(vec, low + 1, high - 1);
}



int main() {
    int n;
    std::cout << "Enter number of elements\n";
    std::cin >> n;
    std::vector<int> v(n);
    std::cout << "Enter all the elements\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }

    int method;
    std::cout << "Enter method: \n\t0: iterative\n\t1: recursive:\t";
    std::cin >> method;

    if (method == 0) {
        CocktailSelectionSort(&v, 0, n - 1);
    } else if (method == 1) {
        CocktailSelectionSort_v2(&v, 0, n - 1);
    } else {
        std::cerr << "Unknown method" << std::endl;
        return -1;
    }
    std::cout << "Sorted elements are\n";
    for (int i = 0; i < n; ++i) {
        std::cout << v[i] << " ";
    }

    return 0;
}
