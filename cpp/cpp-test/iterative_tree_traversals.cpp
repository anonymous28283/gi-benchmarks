







namespace others {

namespace iterative_tree_traversals {

struct Node {
    int64_t data = 0;
    struct Node *left{};
    struct Node *right{};
};


class BinaryTree {
 public:
    Node *createNewNode(
        int64_t);
    std::vector<int64_t> preOrderIterative(
        Node *);

    std::vector<int64_t> postOrderIterative(
        Node *);

    std::vector<int64_t> inOrderIterative(
        Node *);

};


Node *BinaryTree::createNewNode(int64_t data) {
    Node *node = new Node();
    node->data = data;
    node->left = node->right = nullptr;
    return node;
}


std::vector<int64_t> BinaryTree::preOrderIterative(Node *root) {
    std::stack<Node *>
        stack;
    std::vector<int64_t> result;

    stack.push(root);

    while (!stack.empty()) {
        result.push_back(stack.top()->data);
        Node *current = stack.top();
        stack.pop();

        if (current->right) {
            stack.push(current->right);
        }
        if (current->left) {
            stack.push(current->left);
        }
    }

    return result;
}


std::vector<int64_t> BinaryTree::postOrderIterative(Node *root) {
    std::stack<Node *>
        stack;
    std::vector<int64_t> result;

    stack.push(root);

    while (!stack.empty()) {
        result.push_back(stack.top()->data);
        Node *current = stack.top();
        stack.pop();

        if (current->left) {
            stack.push(current->left);
        }
        if (current->right) {
            stack.push(current->right);
        }
    }

    reverse(result.begin(), result.end());

    return result;
}


std::vector<int64_t> BinaryTree::inOrderIterative(Node *root) {
    std::stack<Node *>
        stack;
    std::vector<int64_t> result;

    Node *current = root;

    while (!stack.empty() || current) {
        while (current) {
            stack.push(current);
            current = current->left;
        }
        current = stack.top();
        stack.pop();
        result.push_back(current->data);
        current = current->right;
    }
    return result;
}
void deleteAll(Node *root) {
    if (root) {
        std::stack<Node *> stack;
        stack.push(root);

        while (!stack.empty()) {
            const Node *current = stack.top();
            stack.pop();

            if (current->right) {
                stack.push(current->right);
            }
            if (current->left) {
                stack.push(current->left);
            }
            delete current;
        }
    }
}
}
}


static void test1(others::iterative_tree_traversals::BinaryTree binaryTree,
                  others::iterative_tree_traversals::Node *root) {
    std::vector<int64_t> actual_result{1, 2, 4, 5, 3};
    std::vector<int64_t>
        result;



    result = binaryTree.preOrderIterative(root);


    for (int i = 0; i < result.size(); i++) {
        assert(actual_result[i] == result[i]);
    }


    std::cout << "\nPreOrder Traversal Is : " << std::endl;
    for (auto i : result) {
        std::cout << i << "  ";
    }
}


static void test2(others::iterative_tree_traversals::BinaryTree binaryTree,
                  others::iterative_tree_traversals::Node *root) {
    std::vector<int64_t> actual_result{4, 5, 2, 3, 1};
    std::vector<int64_t>
        result;



    result = binaryTree.postOrderIterative(root);


    for (int i = 0; i < result.size(); i++) {
        assert(actual_result[i] == result[i]);
    }


    std::cout << "\nPostOrder Traversal Is : " << std::endl;
    for (auto i : result) {
        std::cout << i << "  ";
    }
}


static void test3(others::iterative_tree_traversals::BinaryTree binaryTree,
                  others::iterative_tree_traversals::Node *root) {
    std::vector<int64_t> actual_result{4, 2, 5, 1, 3};
    std::vector<int64_t>
        result;



    result = binaryTree.inOrderIterative(root);


    for (int i = 0; i < result.size(); i++) {
        assert(actual_result[i] == result[i]);
    }


    std::cout << "\nInOrder Traversal Is : " << std::endl;
    for (auto i : result) {
        std::cout << i << "  ";
    }
}


static void test4(others::iterative_tree_traversals::BinaryTree binaryTree,
                  others::iterative_tree_traversals::Node *root) {
    std::vector<int64_t> actual_result{-1, -2, -4, -5, -3};
    std::vector<int64_t>
        result;



    result = binaryTree.preOrderIterative(root);


    for (int i = 0; i < result.size(); i++) {
        assert(actual_result[i] == result[i]);
    }


    std::cout << "\nPreOrder Traversal Is : " << std::endl;
    for (auto i : result) {
        std::cout << i << "  ";
    }
}


static void test5(others::iterative_tree_traversals::BinaryTree binaryTree,
                  others::iterative_tree_traversals::Node *root) {
    std::vector<int64_t> actual_result{-4, -5, -2, -3, -1};
    std::vector<int64_t>
        result;



    result = binaryTree.postOrderIterative(root);


    for (int i = 0; i < result.size(); i++) {
        assert(actual_result[i] == result[i]);
    }


    std::cout << "\nPostOrder Traversal Is : " << std::endl;
    for (auto i : result) {
        std::cout << i << "  ";
    }
}


static void test6(others::iterative_tree_traversals::BinaryTree binaryTree,
                  others::iterative_tree_traversals::Node *root) {
    std::vector<int64_t> actual_result{-4, -2, -5, -1, -3};
    std::vector<int64_t>
        result;



    result = binaryTree.inOrderIterative(root);


    for (int i = 0; i < result.size(); i++) {
        assert(actual_result[i] == result[i]);
    }


    std::cout << "\nInOrder Traversal Is : " << std::endl;
    for (auto i : result) {
        std::cout << i << "  ";
    }
}


int main() {



    others::iterative_tree_traversals::BinaryTree
        binaryTree;

    others::iterative_tree_traversals::Node *root = binaryTree.createNewNode(1);
    root->left = binaryTree.createNewNode(2);
    root->right = binaryTree.createNewNode(3);
    root->left->left = binaryTree.createNewNode(4);
    root->left->right = binaryTree.createNewNode(5);

    std::cout << "\n| Tests for positive data value |" << std::endl;
    test1(binaryTree, root);
    std::cout << "\nPre-order test Passed!" << std::endl;

    test2(binaryTree, root);
    std::cout << "\nPost-order test Passed!" << std::endl;

    test3(binaryTree, root);
    std::cout << "\nIn-order test Passed!" << std::endl;


    root->data = -1;
    root->left->data = -2;
    root->right->data = -3;
    root->left->left->data = -4;
    root->left->right->data = -5;

    std::cout << "\n| Tests for negative data values |" << std::endl;
    test4(binaryTree, root);
    std::cout << "\nPre-order test on-negative value Passed!" << std::endl;

    test5(binaryTree, root);
    std::cout << "\nPost-order test on-negative value Passed!" << std::endl;

    test6(binaryTree, root);
    std::cout << "\nIn-order test on-negative value Passed!" << std::endl;

    deleteAll(root);

    return 0;
}
