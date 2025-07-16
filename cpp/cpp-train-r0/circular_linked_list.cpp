






namespace operations_on_datastructures {


namespace circular_linked_list {


struct Node {
    int64_t data;
    Node* next;

    explicit Node(int64_t _data) {
        data = _data;
        next = nullptr;
    }

    explicit Node(int64_t _data, Node* _next) {
        data = _data;
        next = _next;
    }
};


class CircularLinkedList {
 private:
    Node* root;
    Node* end{};

 public:

    CircularLinkedList() {
        root = nullptr;
        end = nullptr;
    }

    CircularLinkedList(const CircularLinkedList& copy) {
        erase();
        root = nullptr;
        Node* node = copy.root;
        while (node != nullptr) {
            insert(node->data);
            node = node->next;
        }
    }

    CircularLinkedList(CircularLinkedList&& source) noexcept {
        root = source.root;
        end = source.end;
        source.root = nullptr;
        source.end = nullptr;
    }

    CircularLinkedList& operator=(const CircularLinkedList& other) {
        erase();
        root = nullptr;
        Node* node = other.root;
        while (node != nullptr) {
            insert(node->data);
            node = node->next;
        }
        return *this;
    }

    CircularLinkedList& operator=(CircularLinkedList&& other) noexcept {
        root = other.root;
        end = other.end;
        other.root = nullptr;
        other.end = nullptr;
        return *this;
    }

    ~CircularLinkedList() { erase(); }

    void erase() {
        if (root == nullptr) {
            return;
        }
        Node* node = root;
        do {
            Node* temp = node;
            node = node->next;
            delete (temp);
        } while (node != root);
        root = nullptr;
        end = nullptr;
    }

    void insert(const std::vector<int64_t>& values) {
        for (int64_t value : values) {
            insert(value);
        }
    }

    void insert(int64_t data) {
        Node* node = new Node(data, root);
        insert(node);
    }

    void insert(Node* node) {
        if (root == nullptr) {
            root = node;
            node->next = root;
            end = root;
        } else {
            end->next = node;
            node->next = root;
            end = node;
        }
    }

    void print() { print(root); }

    void print(Node* root) {
        Node* temp = root;
        if (root == nullptr) {
            std::cout << "Empty List!\n";
            return;
        }
        do {
            std::cout << temp->data << " ";
            temp = temp->next;
        } while (temp != root);
        std::cout << "\n";
    }

    std::vector<int64_t> values() { return values(root); }

    std::vector<int64_t> values(Node* root) {
        std::vector<int64_t> res;
        if (root == nullptr) {
            return res;
        }
        Node* temp = root;
        do {
            res.push_back(temp->data);
            temp = temp->next;
        } while (temp != root);
        return res;
    }
};

}

}


namespace tests {
using operations_on_datastructures::circular_linked_list::CircularLinkedList;
using operations_on_datastructures::circular_linked_list::Node;

void test1() {
    std::cout << "TEST CASE 1\n";
    std::cout << "Intialized a = {2}\n";
    std::cout << "Expected result: {2}\n";
    CircularLinkedList a;
    std::vector<int64_t> res = {2};
    a.insert(2);
    assert(a.values() == res);
    a.print();
    std::cout << "TEST PASSED!\n\n";
}

void test2() {
    std::cout << "TEST CASE 2\n";
    std::cout << "Intialized a = {2, 5, 6}\n";
    std::cout << "Expected result: {2, 5, 6}\n";
    CircularLinkedList a;
    std::vector<int64_t> res = {2, 5, 6};
    a.insert(2);
    a.insert(5);
    a.insert(6);
    assert(a.values() == res);
    a.print();
    std::cout << "TEST PASSED!\n\n";
}

void test3() {
    std::cout << "TEST CASE 3\n";
    std::cout << "Intialized a = {2, 7, 8, 3, 2, 6}\n";
    std::cout << "Expected result: {2, 7, 8, 3, 2, 6}\n";
    CircularLinkedList a;
    std::vector<int64_t> res = {2, 7, 8, 3, 2, 6};
    a.insert({2, 7, 8, 3, 2, 6});
    a.print();
    assert(a.values() == res);
    std::cout << "TEST PASSED!\n\n";
}

void test4() {
    std::cout << "TEST CASE 4\n";
    std::cout << "Intialized a = {2, 5}\n";
    std::cout << "Expected result: {5, 2}\n";
    CircularLinkedList a;
    std::vector<int64_t> res = {5, 2};
    a.insert(2);
    Node* start = new Node(5);
    a.insert(start);
    assert(a.values(start) == res);
    a.print(start);
    std::cout << "TEST PASSED!\n\n";
}


void test5() {
    std::cout << "TEST CASE 5\n";
    std::cout << "Intialized a = {}\n";
    std::cout << "Expected result: Empty List!\n";
    CircularLinkedList a;
    std::vector<int64_t> res = {};
    assert(a.values() == res);
    a.print();
    std::cout << "TEST PASSED!\n\n";
}
}


static void test() {
    tests::test1();
    tests::test2();
    tests::test3();
    tests::test4();
    tests::test5();
}


int main() {
    test();
    return 0;
}
