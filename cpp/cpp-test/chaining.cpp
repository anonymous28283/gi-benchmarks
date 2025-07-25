






class hash_chain {
 private:

    using Node = struct Node {
        int data{};
        std::shared_ptr<struct Node> next;
    };

    std::vector<std::shared_ptr<Node>> head;
    int _mod;

 public:

    explicit hash_chain(int mod) : _mod(mod) {
        while (mod--) head.push_back(nullptr);
    }


    void add(int x, int h) {
        std::shared_ptr<Node> curr;
        std::shared_ptr<Node> temp(new Node);
        temp->data = x;
        temp->next = nullptr;
        if (!head[h]) {
            head[h] = temp;
            curr = head[h];
        } else {
            curr = head[h];
            while (curr->next) curr = curr->next;
            curr->next = temp;
        }
    }


    void display() {
        std::shared_ptr<Node> temp = nullptr;
        int i = 0;
        for (i = 0; i < _mod; i++) {
            if (!head[i]) {
                std::cout << "Key " << i << " is empty" << std::endl;
            } else {
                std::cout << "Key " << i << " has values = " << std::endl;
                temp = head[i];
                while (temp->next) {
                    std::cout << temp->data << " " << std::endl;
                    temp = temp->next;
                }
                std::cout << temp->data;
                std::cout << std::endl;
            }
        }
    }


    virtual int hash(int x) const { return x % _mod; }


    bool find(int x, int h) const {
        std::shared_ptr<Node> temp = head[h];
        if (!head[h]) {

            std::cout << "Element not found" << std::endl;
            return false;
        }


        while (temp->data != x && temp->next) temp = temp->next;

        if (temp->next) {
            std::cout << "Element found" << std::endl;
            return true;
        }



        if (temp->data == x) {
            std::cout << "Element found" << std::endl;
            return true;
        }


        std::cout << "Element not found" << std::endl;
        return false;
    }
};


int main() {
    int c = 0, x = 0, mod = 0, h = 0;
    std::cout << "Enter the size of Hash Table. = " << std::endl;
    std::cin >> mod;

    hash_chain mychain(mod);

    bool loop = true;
    while (loop) {
        std::cout << std::endl;
        std::cout << "PLEASE CHOOSE -" << std::endl;
        std::cout << "1. Add element." << std::endl;
        std::cout << "2. Find element." << std::endl;
        std::cout << "3. Generate Hash." << std::endl;
        std::cout << "4. Display Hash table." << std::endl;
        std::cout << "5. Exit." << std::endl;
        std::cin >> c;
        switch (c) {
            case 1:
                std::cout << "Enter element to add = " << std::endl;
                std::cin >> x;
                h = mychain.hash(x);
                h = std::abs(h);
                mychain.add(x, h);
                break;
            case 2:
                std::cout << "Enter element to search = " << std::endl;
                std::cin >> x;
                h = mychain.hash(x);
                mychain.find(x, h);
                break;
            case 3:
                std::cout << "Enter element to generate hash = " << std::endl;
                std::cin >> x;
                std::cout << "Hash of " << x << " is = " << mychain.hash(x)
                          << std::endl;
                break;
            case 4:
                mychain.display();
                break;
            default:
                loop = false;
                break;
        }
        std::cout << std::endl;
    }

    return 0;
}
