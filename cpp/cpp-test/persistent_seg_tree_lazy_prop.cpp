





namespace range_queries {


class perSegTree {
 private:
    class Node {
     public:
        std::shared_ptr<Node> left = nullptr;
        std::shared_ptr<Node> right = nullptr;
        int64_t val = 0, prop = 0;
    };

    uint32_t n = 0;
    std::vector<std::shared_ptr<Node>>
        ptrs{};


    std::vector<int64_t> vec{};



    std::shared_ptr<Node> newKid(std::shared_ptr<Node> const &curr) {
        auto newNode = std::make_shared<Node>(Node());
        newNode->left = curr->left;
        newNode->right = curr->right;
        newNode->prop = curr->prop;
        newNode->val = curr->val;
        return newNode;
    }


    void lazy(const uint32_t &i, const uint32_t &j,
              std::shared_ptr<Node> const &curr) {
        if (!curr->prop) {
            return;
        }
        curr->val += (j - i + 1) * (curr->prop);
        if (i != j) {
            curr->left = newKid(curr->left);
            curr->right = newKid(curr->right);
            curr->left->prop += curr->prop;
            curr->right->prop += curr->prop;
        }
        curr->prop = 0;
    }


    std::shared_ptr<Node> construct(const uint32_t &i, const uint32_t &j) {
        auto newNode = std::make_shared<Node>(Node());
        if (i == j) {
            newNode->val = vec[i];
        } else {
            uint32_t mid = i + (j - i) / 2;
            auto leftt = construct(i, mid);
            auto right = construct(mid + 1, j);
            newNode->val = leftt->val + right->val;
            newNode->left = leftt;
            newNode->right = right;
        }
        return newNode;
    }


    std::shared_ptr<Node> update(const uint32_t &i, const uint32_t &j,
                                 const uint32_t &l, const uint32_t &r,
                                 const int64_t &value,
                                 std::shared_ptr<Node> const &curr) {
        lazy(i, j, curr);
        if (i >= l && j <= r) {
            std::shared_ptr<Node> newNode = newKid(curr);
            newNode->prop += value;
            lazy(i, j, newNode);
            return newNode;
        }
        if (i > r || j < l) {
            return curr;
        }
        auto newNode = std::make_shared<Node>(Node());
        uint32_t mid = i + (j - i) / 2;
        newNode->left = update(i, mid, l, r, value, curr->left);
        newNode->right = update(mid + 1, j, l, r, value, curr->right);
        newNode->val = newNode->left->val + newNode->right->val;
        return newNode;
    }


    int64_t query(const uint32_t &i, const uint32_t &j, const uint32_t &l,
                  const uint32_t &r, std::shared_ptr<Node> const &curr) {
        lazy(i, j, curr);
        if (j < l || r < i) {
            return 0;
        }
        if (i >= l && j <= r) {
            return curr->val;
        }
        uint32_t mid = i + (j - i) / 2;
        return query(i, mid, l, r, curr->left) +
               query(mid + 1, j, l, r, curr->right);
    }


 public:

    void construct(const std::vector<int64_t>
                       &vec)

    {
        if (vec.empty()) {
            return;
        }
        n = vec.size();
        this->vec = vec;
        auto root = construct(0, n - 1);
        ptrs.push_back(root);
    }


    void update(const uint32_t &l, const uint32_t &r,
                const int64_t
                    &value)

    {
        ptrs.push_back(update(
            0, n - 1, l, r, value,
            ptrs[ptrs.size() -
                 1]));
    }


    int64_t query(
        const uint32_t &l, const uint32_t &r,
        const uint32_t
            &version)

    {
        return query(0, n - 1, l, r, ptrs[version]);
    }


    uint32_t size()


    {
        return ptrs.size();
    }
};
}


static void test() {
    std::vector<int64_t> arr = {-5, 2, 3, 11, -2, 7, 0, 1};
    range_queries::perSegTree tree;
    std::cout << "Elements before any updates are {";
    for (uint32_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i != arr.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "}\n";
    tree.construct(
        arr);
    std::cout << "Querying range sum on version 0 from index 2 to 4 = 3+11-2 = "
              << tree.query(2, 4, 0) << '\n';
    std::cout
        << "Subtract 7 from all elements from index 1 to index 5 inclusive\n";
    tree.update(1, 5, -7);
    std::cout << "Elements of the segment tree whose version = 1 (after 1 "
                 "update) are {";
    for (uint32_t i = 0; i < arr.size(); ++i) {
        std::cout << tree.query(i, i, 1);
        if (i != arr.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "}\n";
    std::cout << "Add 10 to all elements from index 0 to index 7 inclusive\n";
    tree.update(0, 7, 10);
    std::cout << "Elements of the segment tree whose version = 2 (after 2 "
                 "updates) are {";
    for (uint32_t i = 0; i < arr.size(); ++i) {
        std::cout << tree.query(i, i, 2);
        if (i != arr.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "}\n";
    std::cout << "Number of segment trees (versions) now = " << tree.size()
              << '\n';
    std::cout << "Querying range sum on version 0 from index 3 to 5 = 11-2+7 = "
              << tree.query(3, 5, 0) << '\n';
    std::cout << "Querying range sum on version 1 from index 3 to 5 = 4-9+0 = "
              << tree.query(3, 5, 1) << '\n';
}


int main() {
    test();
    return 0;
}
