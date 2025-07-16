




namespace sorting {

    namespace strand {

        template <typename T>
        std::list<T> strand_sort(std::list<T> lst) {
            if (lst.size() < 2) {
                return lst;
            }
            std::list<T> result;
            std::list<T> sorted;
            while(!lst.empty())  {
                sorted.push_back(lst.front());
                lst.pop_front();
                for (auto it = lst.begin(); it != lst.end(); ) {
                    if (sorted.back() <= *it) {
                        sorted.push_back(*it);
                        it = lst.erase(it);
                    } else {
                        it++;
                    }
                }
                result.merge(sorted);
            }
            return result;
        }
    }
}


static void test() {
    std::list<int> lst = { -333, 525, 1, 0, 94, 52, 33 };

    std::cout << "Before: ";
    for(auto item: lst) {
        std::cout << item << " ";
    }

    lst = sorting::strand::strand_sort(lst);

    std::cout << "\nAfter: ";
    for(auto item: lst) {
        std::cout << item << " ";
    }
}


int main() {
    test();
    return 0;
}
