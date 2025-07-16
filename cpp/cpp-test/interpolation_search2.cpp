



int InterpolationSearch(int A[], int n, int x) {
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = low + (((high - 1) * (x - A[low])) / (A[high] - A[low]));
        if (x == A[mid])
            return mid;
        else if (x < A[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    return -1;
}


int main() {
    int A[] = {2, 4, 5, 7, 13, 14, 15, 23};
    int x = 17;


    int index = InterpolationSearch(A, 8, x);
    if (index < 0)
        std::cout << "Number " << x << " not found" << std::endl;
    else
        std::cout << "Number " << x << " is at " << index << std::endl;
}




