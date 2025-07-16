








namespace others {

namespace lru_cache {

class LRUCache {
    uint64_t pageFrame;
    std::list<uint64_t> cache;
    std::unordered_map<uint64_t, std::list<uint64_t>::iterator>
        pageMap;

    uint64_t hits =
        0;

    uint64_t pageFault = 0;


 public:

    explicit LRUCache(uint64_t pf) { pageFrame = pf; }


    void refer(uint64_t page) {

        if (pageMap.find(page) == pageMap.end()) {
            pageFault++;


            if (cache.size() == pageFrame) {

                uint64_t lastPage = cache.back();
                cache.pop_back();
                pageMap.erase(lastPage);
            }
        }

        else {
            hits++;

            cache.erase(pageMap[page]);
        }


        cache.push_front(page);
        pageMap[page] = cache.begin();
    }


    void display() {
        for (uint64_t &it : cache) {
            std::cout << it << " ";
        }
        std::cout << std::endl;
    }

    uint64_t getHits() const { return hits; }

    uint64_t getPageFault() const { return pageFault; }
};

}
}

namespace lru_tests {

template <typename T>
void log(T msg) {

    std::cout << "[TESTS] : ---> " << msg << std::endl;
}


static void test_1() {
    uint64_t expected_hits = 2;
    uint64_t expected_pageFault = 4;

    log("Running Test-1...");

    others::lru_cache::LRUCache cache(4);
    cache.refer(1);
    cache.refer(2);
    cache.refer(5);
    cache.refer(1);
    cache.refer(4);
    cache.refer(5);

    log("Checking assert statement...");
    assert(cache.getHits() == expected_hits &&
           cache.getPageFault() == expected_pageFault);
    log("Assert successful!");
    log("Test-1 complete!");
}


static void test_2() {
    uint64_t expected_hits = 4;
    uint64_t expected_pageFault = 2;

    log("Running Test-2...");

    others::lru_cache::LRUCache cache(4);
    cache.refer(1);
    cache.refer(1);
    cache.refer(1);
    cache.refer(1);
    cache.refer(1);
    cache.refer(5);

    log("Checking assert statement...");
    assert(cache.getHits() == expected_hits &&
           cache.getPageFault() == expected_pageFault);
    log("Assert successful!");
    log("Test-2 complete!");
}


static void test_3() {
    uint64_t expected_hits = 1;
    uint64_t expected_pageFault = 5;

    log("Running Test-3...");

    others::lru_cache::LRUCache cache(4);
    cache.refer(1);
    cache.refer(2);
    cache.refer(3);
    cache.refer(4);
    cache.refer(5);
    cache.refer(5);

    log("Checking assert statement...");
    assert(cache.getHits() == expected_hits &&
           cache.getPageFault() == expected_pageFault);
    log("Assert successful!");
    log("Test-3 complete!");
}


static void run_tests() {
    test_1();
    test_2();
    test_3();
    log("");
    log("TESTS COMPLETED!");
}
}


int main() {
    lru_tests::run_tests();


    others::lru_cache::LRUCache cache(4);
    cache.refer(1);
    cache.refer(2);
    cache.refer(3);
    cache.refer(4);
    cache.refer(5);
    cache.refer(5);

    cache.display();

    std::cout << "Hits: " << cache.getHits()
              << " Miss: " << cache.getPageFault() << std::endl;
    return 0;
}
