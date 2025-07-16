







namespace operations_on_datastructures {


namespace reverse_binary_tree {


struct Node {
    int64_t data;
    Node* left;
    Node* right;

    explicit Node(int64_t _data) {
        data = _data;
        left = nullptr;
        right = nullptr;
    }
};


class BinaryTree {
 private:
    Node* root;

    Node* insert(int64_t data, Node* pivot) {
        if (pivot == nullptr) {
            return new Node(data);
        }
        if (data <= pivot->data) {
            pivot->left =
                insert(data, pivot->left);
        } else {
            pivot->right =
                insert(data, pivot->right);
        }
        return pivot;
    }

    Node* reverseBinaryTree(Node* pivot) {
        if (pivot == nullptr) {
            return pivot;
        }
        Node* temp = pivot->left;
        pivot->left = reverseBinaryTree(pivot->right);
        pivot->right = reverseBinaryTree(temp);
        return pivot;
    }

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

 public:

    BinaryTree() { root = nullptr; }

    explicit BinaryTree(int64_t data) { root = new Node(data); }

    ~BinaryTree() {
        std::vector<Node*> nodes;
        nodes.emplace_back(root);
        while (!nodes.empty()) {
            const auto cur_node = nodes.back();
            nodes.pop_back();
            if (cur_node) {
                nodes.emplace_back(cur_node->left);
                nodes.emplace_back(cur_node->right);
                delete cur_node;
            }
        }
    }


    void add(int64_t data) { root = insert(data, root); }

    void reverse() { root = reverseBinaryTree(root); }

    std::vector<int64_t> get_level_order() {
        std::vector<int64_t> data;
        if (root == nullptr) {
            return data;
        }
        std::queue<Node*> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            Node* temp = nodes.front();
            data.push_back(temp->data);
            nodes.pop();
            if (temp->left != nullptr) {
                nodes.push(temp->left);
            }
            if (temp->right != nullptr) {
                nodes.push(temp->right);
            }
        }
        return data;
    }

    void print() {
        for (int i : get_level_order()) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
};

}
}


namespace tests {
using operations_on_datastructures::reverse_binary_tree::
    BinaryTree;

void test1() {
    BinaryTree bst;
    std::vector<int64_t> pre_reversal, post_reversal;
    std::cout << "TEST CASE 1\n";
    std::cout << "Initializing tree with a single element (5)\n";
    bst.add(5);
    pre_reversal = bst.get_level_order();
    std::cout << "Before reversal: ";
    bst.print();
    std::cout << "After reversal: ";
    bst.reverse();
    post_reversal = bst.get_level_order();
    assert(pre_reversal.size() ==
           post_reversal.size());
    assert(pre_reversal.size() ==
           1);
    assert(pre_reversal[0] ==
           post_reversal[0]);
    bst.print();
    std::cout << "TEST PASSED!\n\n";
}

void test2() {
    BinaryTree bst;
    std::vector<int64_t> pre_reversal, post_reversal;
    std::cout << "TEST CASE 2\n";
    std::cout << "Creating empty tree (root points to NULL)\n";
    pre_reversal = bst.get_level_order();
    std::cout << "Before reversal: ";
    bst.print();
    std::cout << "After reversal: ";
    bst.reverse();
    post_reversal = bst.get_level_order();
    assert(pre_reversal.size() ==
           post_reversal.size());
    assert(pre_reversal.size() ==
           0);
    bst.print();
    std::cout << "TEST PASSED!\n\n";
}

void test3() {
    BinaryTree bst;
    std::vector<int64_t> pre_reversal, post_reversal;
    std::vector<int64_t> pre_res = {4, 3, 6, 2, 5, 7, 1};
    std::vector<int64_t> post_res = {4, 6, 3, 7, 5, 2, 1};
    std::cout << "TEST CASE 3\n";
    std::cout << "Creating tree with elements (4, 6, 3, 2, 5, 7, 1)\n";
    bst.add(4);
    bst.add(6);
    bst.add(3);
    bst.add(2);
    bst.add(5);
    bst.add(7);
    bst.add(1);
    pre_reversal = bst.get_level_order();
    assert(pre_reversal == pre_res);
    std::cout << "Before reversal: ";
    bst.print();
    std::cout << "After reversal: ";
    bst.reverse();
    post_reversal = bst.get_level_order();
    assert(post_reversal == post_res);
    bst.print();
    std::cout << "TEST PASSED!\n\n";
}
}


static void test() {
    tests::test1();
    tests::test2();
    tests::test3();
}


int main() {
    test();
    return 0;
}
