







namespace others {


namespace Cache {


template <typename T>
class D_Node {
 public:
    T data;
    D_Node<T> *prev;
    D_Node<T> *next;

    explicit D_Node(T data) : data(data), prev(nullptr), next(nullptr) {}
};

template <typename K, typename V>
using CacheNode = D_Node<std::pair<K, V>>;


template <typename K, typename V>
class LRUCache {
    CacheNode<K, V> *head;
    CacheNode<K, V> *tail;
    std::uint32_t _capacity;

    std::unordered_map<K, CacheNode<K, V> *>
        node_map;

 public:

    explicit LRUCache(int _capacity)
        : head(nullptr), tail(nullptr), _capacity(_capacity) {}

 private:

    void push_front(CacheNode<K, V> *node_ptr) {
        if (!head) {
            head = node_ptr;
            tail = node_ptr;
            return;
        }

        node_ptr->next = head;
        head->prev = node_ptr;
        head = node_ptr;
    }


    void make_recent(CacheNode<K, V> *node_ptr) {
        if (head == node_ptr) {
            return;
        }

        CacheNode<K, V> *prev = node_ptr->prev;
        CacheNode<K, V> *next = node_ptr->next;

        prev->next = next;
        if (next) {
            next->prev = prev;
        } else {
            tail = prev;
        }

        node_ptr->prev = nullptr;
        node_ptr->next = nullptr;
        push_front(node_ptr);
    }


    void pop_back() {
        if (!head) {
            return;
        }
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }

        CacheNode<K, V> *temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
    }

 public:

    void put(K key, V value) {

        if (node_map.count(key)) {
            node_map[key]->data.second = value;
            make_recent(node_map[key]);
            return;
        }



        if (node_map.size() == _capacity) {
            node_map.erase(tail->data.first);
            pop_back();
        }

        CacheNode<K, V> *newNode = new CacheNode<K, V>({key, value});

        node_map[key] = newNode;
        push_front(newNode);
    }


    V get(K key) {
        if (!node_map.count(key)) {
            throw std::runtime_error("key is not present in the cache");
        }


        V value = node_map[key]->data.second;
        make_recent(node_map[key]);
        return value;
    }


    int size() const { return node_map.size(); }


    int capacity() const { return _capacity; }


    bool empty() const { return node_map.empty(); }


    ~LRUCache() {
        auto it = node_map.begin();
        while (it != node_map.end()) {
            delete it->second;
            ++it;
        }
    }
};
}
}


static void test() {
    others::Cache::LRUCache<int, int> cache(5);


    assert(cache.size() == 0);
    assert(cache.capacity() == 5);
    assert(cache.empty());


    cache.put(1, 10);
    cache.put(-2, 20);


    assert(cache.size() == 2);
    assert(cache.capacity() == 5);
    assert(!cache.empty());


    assert(cache.get(1) == 10);
    assert(cache.get(-2) == 20);

    cache.put(-3, -30);
    cache.put(4, 40);
    cache.put(5, -50);
    cache.put(6, 60);


    assert(cache.size() == 5);
    assert(cache.capacity() == 5);
    assert(!cache.empty());




    try {
        cache.get(1);
    } catch (const std::runtime_error &e) {
        assert(std::string(e.what()) == "key is not present in the cache");
    }


    assert(cache.get(-2) == 20);
    assert(cache.get(-3) == -30);
    assert(cache.get(4) == 40);
    assert(cache.get(5) == -50);
    assert(cache.get(6) == 60);

    std::cout << "test - passed\n";
}


int main() {
    test();
    return 0;
}
