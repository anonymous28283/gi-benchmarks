





void bucketSort(float arr[], int n) {

    std::vector<float> *b = new std::vector<float>[n];


    for (int i = 0; i < n; i++) {
        int bi = n * arr[i];
        b[bi].push_back(arr[i]);
    }


    for (int i = 0; i < n; i++) std::sort(b[i].begin(), b[i].end());


    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++) arr[index++] = b[i][j];
    delete[] b;
}


int main() {
    float arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n = sizeof(arr) / sizeof(arr[0]);
    bucketSort(arr, n);

    std::cout << "Sorted array is \n";
    for (int i = 0; i < n; i++) std::cout << arr[i] << " ";
    return 0;
}
