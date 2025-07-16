







namespace others {


namespace recursive_tree_traversals {


struct Node {
    std::uint64_t data = 0;
    struct Node *left{};
    struct Node *right{};
};

class BT {
 public:
    std::vector<std::uint64_t>
        inorder_result;
    std::vector<std::uint64_t>
        preorder_result;
    std::vector<std::uint64_t>
        postorder_result;


    Node *createNewNode(
        std::uint64_t);

    std::vector<std::uint64_t> inorder(
        Node *);

    std::vector<std::uint64_t> preorder(
        Node *);

    std::vector<std::uint64_t> postorder(
        Node *);

};


Node *BT::createNewNode(std::uint64_t data) {
    Node *node = new Node();
    node->data = data;
    node->left = node->right = nullptr;
    return node;
}


std::vector<std::uint64_t> BT::inorder(Node *root) {
    if (root == nullptr) {
        return {};
    }

    inorder(root->left);
    BT::inorder_result.push_back(
        root->data);
    inorder(root->right);

    return inorder_result;
}


std::vector<std::uint64_t> BT::preorder(Node *root) {
    if (root == nullptr) {
        return {};
    }

    BT::preorder_result.push_back(
        root->data);
    preorder(root->left);
    preorder(root->right);

    return preorder_result;
}


std::vector<std::uint64_t> BT::postorder(Node *root) {
    if (root == nullptr) {
        return {};
    }

    postorder(root->left);
    postorder(root->right);
    BT::postorder_result.push_back(
        root->data);

    return postorder_result;
}

void deleteAll(const Node *const root) {
    if (root) {
        deleteAll(root->left);
        deleteAll(root->right);
        delete root;
    }
}

}

}


void test1() {
    others::recursive_tree_traversals::BT obj1;
    others::recursive_tree_traversals::Node *root = obj1.createNewNode(2);
    root->left = obj1.createNewNode(7);
    root->right = obj1.createNewNode(5);
    root->left->left = obj1.createNewNode(2);
    root->left->right = obj1.createNewNode(6);
    root->right->right = obj1.createNewNode(9);
    root->left->right->left = obj1.createNewNode(5);
    root->left->right->right = obj1.createNewNode(11);
    root->right->right->left = obj1.createNewNode(4);

    std::vector<std::uint64_t> actual_result_inorder{2, 7, 5, 6, 11,
                                                     2, 5, 4, 9};
    std::vector<std::uint64_t> actual_result_preorder{2,  7, 2, 6, 5,
                                                      11, 5, 9, 4};
    std::vector<std::uint64_t> actual_result_postorder{2, 5, 11, 6, 7,
                                                       4, 9, 5,  2};
    std::vector<std::uint64_t>
        result_inorder;

    std::vector<std::uint64_t>
        result_preorder;

    std::vector<std::uint64_t>
        result_postorder;


    std::uint64_t size = actual_result_inorder.size();



    result_inorder = obj1.inorder(root);
    std::cout << "Testcase #1: Inorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_inorder[i] == result_inorder[i]);
    }
    std::cout << "Passed!" << std::endl;



    result_preorder = obj1.preorder(root);
    std::cout << "Testcase #1: Preorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_preorder[i] == result_preorder[i]);
    }
    std::cout << "Passed!" << std::endl;



    result_postorder = obj1.postorder(root);
    std::cout << "Testcase #1: Postorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_postorder[i] == result_postorder[i]);
    }
    std::cout << "Passed!" << std::endl;

    std::cout << std::endl;
    deleteAll(root);
}


void test2() {
    others::recursive_tree_traversals::BT obj2;
    others::recursive_tree_traversals::Node *root = obj2.createNewNode(1);
    root->left = obj2.createNewNode(2);
    root->right = obj2.createNewNode(3);
    root->left->left = obj2.createNewNode(4);
    root->right->left = obj2.createNewNode(5);
    root->right->right = obj2.createNewNode(6);
    root->right->left->left = obj2.createNewNode(7);
    root->right->left->right = obj2.createNewNode(8);

    std::vector<std::uint64_t> actual_result_inorder{4, 2, 1, 7, 5, 8, 3, 6};
    std::vector<std::uint64_t> actual_result_preorder{1, 2, 4, 3, 5, 7, 8, 6};
    std::vector<std::uint64_t> actual_result_postorder{4, 2, 7, 8, 5, 6, 3, 1};
    std::vector<std::uint64_t>
        result_inorder;

    std::vector<std::uint64_t>
        result_preorder;

    std::vector<std::uint64_t>
        result_postorder;


    std::uint64_t size = actual_result_inorder.size();



    result_inorder = obj2.inorder(root);
    std::cout << "Testcase #2: Inorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_inorder[i] == result_inorder[i]);
    }
    std::cout << "Passed!" << std::endl;



    result_preorder = obj2.preorder(root);
    std::cout << "Testcase #2: Preorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_preorder[i] == result_preorder[i]);
    }
    std::cout << "Passed!" << std::endl;



    result_postorder = obj2.postorder(root);
    std::cout << "Testcase #2: Postorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_postorder[i] == result_postorder[i]);
    }
    std::cout << "Passed!" << std::endl;

    std::cout << std::endl;
    deleteAll(root);
}


void test3() {
    others::recursive_tree_traversals::BT obj3;
    others::recursive_tree_traversals::Node *root = obj3.createNewNode(1);
    root->left = obj3.createNewNode(2);
    root->right = obj3.createNewNode(3);
    root->left->left = obj3.createNewNode(4);
    root->left->right = obj3.createNewNode(5);

    std::vector<std::uint64_t> actual_result_inorder{4, 2, 5, 1, 3};
    std::vector<std::uint64_t> actual_result_preorder{1, 2, 4, 5, 3};
    std::vector<std::uint64_t> actual_result_postorder{4, 5, 2, 3, 1};
    std::vector<std::uint64_t>
        result_inorder;

    std::vector<std::uint64_t>
        result_preorder;

    std::vector<std::uint64_t>
        result_postorder;


    std::uint64_t size = actual_result_inorder.size();




    result_inorder = obj3.inorder(root);
    std::cout << "Testcase #3: Inorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_inorder[i] == result_inorder[i]);
    }
    std::cout << "Passed!" << std::endl;



    result_preorder = obj3.preorder(root);
    std::cout << "Testcase #3: Preorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_preorder[i] == result_preorder[i]);
    }
    std::cout << "Passed!" << std::endl;



    result_postorder = obj3.postorder(root);
    std::cout << "Testcase #3: Postorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_postorder[i] == result_postorder[i]);
    }
    std::cout << "Passed!" << std::endl;

    std::cout << std::endl;
    deleteAll(root);
}


static void tests() {
    std::cout << "1st test-case" << std::endl;
    test1();
    std::cout << "2nd test-case" << std::endl;
    test2();
    std::cout << "3rd test-case" << std::endl;
    test3();
}

int main() {
    tests();
    return 0;
}
