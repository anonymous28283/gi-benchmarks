






namespace operations_on_datastructures {


namespace inorder_traversal_of_bst {


class Node {
 public:
    int64_t data;
    Node *left;
    Node *right;
};


Node *makeNode(int64_t data) {
    Node *node = new Node();
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}


Node *Insert(Node *root, int64_t data) {
    if (root == nullptr) {
        root = makeNode(data);
    } else if (data <= root->data) {
        root->left = Insert(root->left, data);
    } else {
        root->right = Insert(root->right, data);
    }
    return root;
}


Node *getNode(Node *root, int64_t data) {
    if (root == nullptr) {
        return nullptr;
    } else if (root->data == data) {
        return root;
    } else if (data > root->data) {


        return getNode(root->right, data);
    } else {


        return getNode(root->left, data);
    }
}


Node *findMinNode(Node *root) {
    if (root == nullptr) {
        return root;
    }
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}


void printInorder(Node *root) {
    if (root == nullptr) {
        return;
    }

    printInorder(root->left);
    std::cout << root->data << " ";
    printInorder(root->right);
}


Node *makeBST(Node *root, const std::vector<int64_t> &data) {
    for (int64_t values : data) {
        root = Insert(root, values);
    }
    return root;
}


Node *getInorderSuccessor(Node *root, int64_t data) {
    Node *current = getNode(root, data);
    if (current == nullptr) {
        return nullptr;
    }


    if (current->right != nullptr) {
        return findMinNode(current->right);
    }

    else {
        Node *successor = nullptr;
        Node *ancestor = root;

        while (ancestor != current && ancestor != nullptr) {

            if (current->data < ancestor->data) {
                successor = ancestor;
                ancestor = ancestor->left;
            } else {
                ancestor = ancestor->right;
            }
        }
        return successor;
    }
}


void deallocate(Node *rootNode) {
    if (rootNode == nullptr) {
        return;
    }
    deallocate(rootNode->left);
    deallocate(rootNode->right);
    delete (rootNode);
}

}
}


class TestCases {
 private:

    template <typename T>
    void log(T msg) {

        std::cout << "[TESTS] : ---> " << msg << std::endl;
    }

 public:

    void runTests() {
        log("Running Tests...");

        testCase_1();
        testCase_2();
        testCase_3();

        log("Test Cases over!");
        std::cout << std::endl;
    }


    void testCase_1() {
        const operations_on_datastructures::inorder_traversal_of_bst::Node
            *expectedOutput = nullptr;

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        log("This is test case 1 : ");
        log("Description:");
        log("   EDGE CASE : Printing inorder successor for last node in the "
            "BST, Output will be nullptr.");

        operations_on_datastructures::inorder_traversal_of_bst::Node *root =
            nullptr;
        std::vector<int64_t> node_data{
            20, 3, 5, 6, 2, 23, 45, 78, 21};

        root = operations_on_datastructures::inorder_traversal_of_bst::makeBST(
            root,
            node_data);

        std::cout << "Inorder sequence is : ";
        operations_on_datastructures::inorder_traversal_of_bst::printInorder(
            root);
        std::cout << std::endl;

        operations_on_datastructures::inorder_traversal_of_bst::Node
            *inorderSuccessor = operations_on_datastructures::
                inorder_traversal_of_bst::getInorderSuccessor(
                    root, 78);

        log("Checking assert expression...");
        assert(inorderSuccessor == expectedOutput);
        log("Assertion check passed!");

        operations_on_datastructures::inorder_traversal_of_bst::deallocate(
            root);

        log("[PASS] : TEST CASE 1 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }


    void testCase_2() {
        const int expectedOutput = 21;

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        log("This is test case 2 : ");

        operations_on_datastructures::inorder_traversal_of_bst::Node *root =
            nullptr;
        std::vector<int64_t> node_data{
            20, 3, 5, 6, 2, 23, 45, 78, 21};

        root = operations_on_datastructures::inorder_traversal_of_bst::makeBST(
            root,
            node_data);

        std::cout << "Inorder sequence is : ";
        operations_on_datastructures::inorder_traversal_of_bst::printInorder(
            root);
        std::cout << std::endl;

        operations_on_datastructures::inorder_traversal_of_bst::Node
            *inorderSuccessor = operations_on_datastructures::
                inorder_traversal_of_bst::getInorderSuccessor(
                    root, 20);

        log("Checking assert expression...");
        assert(inorderSuccessor->data == expectedOutput);
        log("Assertion check passed!");

        operations_on_datastructures::inorder_traversal_of_bst::deallocate(
            root);

        log("[PASS] : TEST CASE 2 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }


    void testCase_3() {
        const int expectedOutput = 110;

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        log("This is test case 3 : ");

        operations_on_datastructures::inorder_traversal_of_bst::Node *root =
            nullptr;
        std::vector<int64_t> node_data{
            89,  67,  32, 56, 90, 123, 120,
            110, 115, 6,  78, 7,  10};

        root = operations_on_datastructures::inorder_traversal_of_bst::makeBST(
            root,
            node_data);

        std::cout << "Inorder sequence is : ";
        operations_on_datastructures::inorder_traversal_of_bst::printInorder(
            root);
        std::cout << std::endl;

        operations_on_datastructures::inorder_traversal_of_bst::Node
            *inorderSuccessor = operations_on_datastructures::
                inorder_traversal_of_bst::getInorderSuccessor(
                    root, 90);

        log("Checking assert expression...");
        assert(inorderSuccessor->data == expectedOutput);
        log("Assertion check passed!");

        operations_on_datastructures::inorder_traversal_of_bst::deallocate(
            root);

        log("[PASS] : TEST CASE 3 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }
};


static void test() {
    TestCases tc;
    tc.runTests();
}


int main(int argc, char *argv[]) {
    test();

    operations_on_datastructures::inorder_traversal_of_bst::Node *root =
        nullptr;
    std::vector<int64_t> node_data{3,  4, 5,
                                   89, 1, 2};

    int64_t targetElement = 4;
    root = operations_on_datastructures::inorder_traversal_of_bst::makeBST(
        root, node_data);

    operations_on_datastructures::inorder_traversal_of_bst::Node
        *inorderSuccessor = operations_on_datastructures::
            inorder_traversal_of_bst::getInorderSuccessor(root, targetElement);

    std::cout << "In-order sequence is : ";
    operations_on_datastructures::inorder_traversal_of_bst::printInorder(root);
    std::cout << std::endl;

    if (inorderSuccessor == nullptr) {
        std::cout << "Inorder successor for last node is NULL" << std::endl;
    } else {
        std::cout << "Target element is : " << targetElement << std::endl;
        std::cout << "Inorder successor for target element is : "
                  << inorderSuccessor->data << std::endl;
    }

    deallocate(root);

    return 0;
}
