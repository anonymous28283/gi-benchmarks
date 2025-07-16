








namespace probability {

namespace windowed_median {
using Window = std::list<int>;
using size_type = Window::size_type;


class WindowedMedian {
    const size_type _windowSize;
    Window _window;
    std::multiset<int> _sortedValues;

    std::multiset<int>::const_iterator
        _itMedian;



    void insertToSorted(int value) {
        _sortedValues.insert(value);
        const auto sz = _sortedValues.size();
        if (sz == 1) {
            _itMedian = _sortedValues.begin();
            return;
        }




        if (value < *_itMedian && sz % 2 == 0) {
            --_itMedian;
        }



        else if (value >= *_itMedian && sz % 2 != 0) {
            ++_itMedian;
        }
    }


    void eraseFromSorted(int value) {
        const auto sz = _sortedValues.size();




        if (value <= *_itMedian && sz % 2 == 0) {
            ++_itMedian;
        }




        else if (value >= *_itMedian && sz % 2 != 0) {
            --_itMedian;
        }



        const auto it = _sortedValues.find(value);
        _sortedValues.erase(it);
    }

 public:

    explicit WindowedMedian(size_type windowSize) : _windowSize(windowSize){};


    void insert(int value) {

        _window.push_back(value);
        insertToSorted(value);
        if (_window.size() > _windowSize) {

            eraseFromSorted(
                _window.front());

            _window.pop_front();

        }
    }


    float getMedian() const {
        if (_sortedValues.size() % 2 != 0) {
            return *_itMedian;
        }
        return 0.5f * *_itMedian + 0.5f * *next(_itMedian);
    }


    float getMedianNaive() const {
        auto window = _window;
        window.sort();
        auto median =
            *next(window.begin(),
                  window.size() / 2);
        if (window.size() % 2 != 0) {
            return median;
        }
        return 0.5f * median +
               0.5f * *next(window.begin(), window.size() / 2 - 1);
    }
};
}
}


static void test(const std::vector<int> &vals, int windowSize) {
    probability::windowed_median::WindowedMedian windowedMedian(windowSize);
    for (const auto val : vals) {
        windowedMedian.insert(val);


        assert(windowedMedian.getMedian() == windowedMedian.getMedianNaive());
    }
}


int main(int argc, const char *argv[]) {

    test({1, 2, 3, 4, 5, 6, 7, 8, 9},
         3);
    test({9, 8, 7, 6, 5, 4, 3, 2, 1},
         3);
    test({9, 8, 7, 6, 5, 4, 5, 6}, 4);
    test({3, 3, 3, 3, 3, 3, 3, 3, 3}, 3);
    test({3, 3, 3, 3, 7, 3, 3, 3, 3}, 3);
    test({4, 3, 3, -5, -5, 1, 3, 4, 5},
         5);




    test({470211272, 101027544, 1457850878, 1458777923, 2007237709, 823564440,
          1115438165, 1784484492, 74243042, 114807987},
         6);


    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<int> vals;
    for (int i = 8; i < 100; i++) {
        const auto n =
            1 + std::rand() /
                    ((RAND_MAX + 5u) / 20);
        auto windowSize =
            1 + std::rand() / ((RAND_MAX + 3u) /
                               10);
        vals.clear();
        vals.reserve(n);
        for (int i = 0; i < n; i++) {
            vals.push_back(
                rand() - RAND_MAX);
        }
        test(vals, windowSize);
    }
    return 0;
}
