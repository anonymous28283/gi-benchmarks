







int minSwaps(int arr[], int n) {



    std::pair<int, int> *arrPos = new std::pair<int, int>[n];
    for (int i = 0; i < n; i++) {
        arrPos[i].first = arr[i];
        arrPos[i].second = i;
    }




    std::sort(arrPos, arrPos + n);



    std::vector<bool> vis(n, false);


    int ans = 0;


    for (int i = 0; i < n; i++) {


        if (vis[i] || arrPos[i].second == i)
            continue;



        int cycle_size = 0;
        int j = i;
        while (!vis[j]) {
            vis[j] = 1;


            j = arrPos[j].second;
            cycle_size++;
        }


        if (cycle_size > 0) {
            ans += (cycle_size - 1);
        }
    }

    delete[] arrPos;


    return ans;
}


int main() {
    int arr[] = {6, 7, 8, 1, 2, 3, 9, 12};
    int n = (sizeof(arr) / sizeof(int));
    std::cout << minSwaps(arr, n);
    return 0;
}
