






namespace range_queries {

class fenwick_tree {
    size_t n = 0;
    std::vector<int> bit{};


    inline int offset(int x) { return (x & (-x)); }
 public:

    template <typename T>
    explicit fenwick_tree(const std::vector<T>& arr) : n(arr.size()) {
        bit.assign(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            update(i, arr[i]);
        }
    }


    template <typename T>
    explicit fenwick_tree(T x) : n(x) { bit.assign(n + 1, 0); }


    template <typename T>
    void update(T id, T val) {
        id++;
        while (id <= n) {
            bit[id] += val;
            id += offset(id);
        }
    }


    template <typename T>
    int sum(T id) {
        id++;
        T res = 0;
        while (id > 0) {
            res += bit[id];
            id -= offset(id);
        }
        return res;
    }


    int sum_range(int l, int r) { return sum(r) - sum(l - 1); }
};
}


static void tests() {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    range_queries::fenwick_tree fenwick_tree(arr);

    assert(fenwick_tree.sum_range(0, 0) == 1);
    assert(fenwick_tree.sum_range(0, 1) == 3);
    assert(fenwick_tree.sum_range(0, 2) == 6);
    assert(fenwick_tree.sum_range(0, 3) == 10);
    assert(fenwick_tree.sum_range(0, 4) == 15);

    fenwick_tree.update(0, 6);
    std::cout << "All tests have successfully passed!\n";
}


int main() {
    tests();
    return 0;
}
