




using std::cout;
using std::endl;
using std::vector;

vector<int> root, rank;


void CreateSet(int n) {
    root = vector<int>(n + 1);
    rank = vector<int>(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        root[i] = i;
    }
}


int Find(int x) {
    if (root[x] == x) {
        return x;
    }
    return root[x] = Find(root[x]);
}


bool InSameUnion(int x, int y) { return Find(x) == Find(y); }


void Union(int x, int y) {
    int a = Find(x), b = Find(y);
    if (a != b) {
        if (rank[a] < rank[b]) {
            root[a] = b;
        } else if (rank[a] > rank[b]) {
            root[b] = a;
        } else {
            root[a] = b;
            ++rank[b];
        }
    }
}


int main() {

    int n = 100;
    CreateSet(n);
    for (int i = 1; i <= 100; ++i) {
        if (root[i] != i) {
            cout << "Fail" << endl;
            break;
        }
    }

    cout << "1 and 2 are initially not in the same subset" << endl;
    if (InSameUnion(1, 2)) {
        cout << "Fail" << endl;
    }
    Union(1, 2);
    cout << "1 and 2 are now in the same subset" << endl;
    if (!InSameUnion(1, 2)) {
        cout << "Fail" << endl;
    }
    return 0;
}
