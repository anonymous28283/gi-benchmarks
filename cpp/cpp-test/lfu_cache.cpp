






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
class LFUCache {
    std::unordered_map<K, std::pair<CacheNode<K, V> *, int>>
        node_map;
    std::unordered_map<int, std::pair<CacheNode<K, V> *, CacheNode<K, V> *>>
        freq_map;

    int minFreq;
    int _capacity;

 public:

    explicit LFUCache(int _capacity) : minFreq(0), _capacity(_capacity) {}

 private:

    void push(int freq, CacheNode<K, V> *node) {


        if (!freq_map.count(freq)) {
            freq_map[freq] = {node, node};
            return;
        }

        std::pair<CacheNode<K, V> *, CacheNode<K, V> *> &p = freq_map[freq];



        p.first->prev = node;
        node->next = p.first;
        p.first = node;
    }


    void increase_frequency(std::pair<CacheNode<K, V> *, int> &p_node) {
        CacheNode<K, V> *node = p_node.first;
        int freq = p_node.second;

        std::pair<CacheNode<K, V> *, CacheNode<K, V> *> &p = freq_map[freq];




        if (p.first == node && p.second == node) {
            freq_map.erase(freq);
            if (minFreq == freq) {
                minFreq = freq + 1;
            }
        } else {

            CacheNode<K, V> *prev = node->prev;
            CacheNode<K, V> *next = node->next;
            node->prev = nullptr;
            node->next = nullptr;

            if (prev) {
                prev->next = next;
            } else {
                p.first = next;
            }

            if (next) {
                next->prev = prev;
            } else {
                p.second = prev;
            }
        }
        push(freq + 1, node);
        ++p_node.second;
    }


    void pop() {
        std::pair<CacheNode<K, V> *, CacheNode<K, V> *> &p = freq_map[minFreq];




        if (p.first == p.second) {
            delete p.first;
            freq_map.erase(minFreq);
            return;
        }


        CacheNode<K, V> *temp = p.second;
        p.second = temp->prev;
        p.second->next = nullptr;
        delete temp;
    }

 public:

    void put(K key, V value) {

        if (node_map.count(key)) {
            node_map[key].first->data.second = value;
            increase_frequency(node_map[key]);
            return;
        }



        if (node_map.size() == _capacity) {
            node_map.erase(freq_map[minFreq].second->data.first);
            pop();
        }


        CacheNode<K, V> *node = new CacheNode<K, V>({key, value});
        node_map[key] = {node, 1};
        minFreq = 1;
        push(1, node);
    }


    V get(K key) {
        if (!node_map.count(key)) {
            throw std::runtime_error("key is not present in the cache");
        }


        V value = node_map[key].first->data.second;
        increase_frequency(node_map[key]);
        return value;
    }


    int size() const { return node_map.size(); }


    int capacity() const { return _capacity; }


    bool empty() const { return node_map.empty(); }


    ~LFUCache() {
        auto it = node_map.begin();
        while (it != node_map.end()) {
            delete it->second.first;
            ++it;
        }
    }
};
}
}


static void test() {
    others::Cache::LFUCache<int, int> cache(5);


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


    assert(cache.get(1) == 10);
    assert(cache.get(-2) == 20);






    assert(cache.get(4) == 40);
    assert(cache.get(5) == -50);
    assert(cache.get(6) == 60);

    std::cout << "test - passed\n";
}


int main() {
    test();
    return 0;
}
