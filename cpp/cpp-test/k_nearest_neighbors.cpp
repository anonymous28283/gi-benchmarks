










namespace machine_learning {


namespace k_nearest_neighbors {


template <typename T>
double euclidean_distance(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<double> aux;
    std::transform(a.begin(), a.end(), b.begin(), std::back_inserter(aux),
                   [](T x1, T x2) { return std::pow((x1 - x2), 2); });
    aux.shrink_to_fit();
    return std::sqrt(std::accumulate(aux.begin(), aux.end(), 0.0));
}


class Knn {
 private:
    std::vector<std::vector<double>> X_{};
    std::vector<int> Y_{};

 public:

    explicit Knn(std::vector<std::vector<double>>& X, std::vector<int>& Y)
        : X_(X), Y_(Y){};


    Knn(const Knn& model) = default;


    Knn& operator=(const Knn& model) = default;


    Knn(Knn&&) = default;


    Knn& operator=(Knn&&) = default;


    ~Knn() = default;


    int predict(std::vector<double>& sample, int k) {
        std::vector<int> neighbors;
        std::vector<std::pair<double, int>> distances;
        for (size_t i = 0; i < this->X_.size(); ++i) {
            auto current = this->X_.at(i);
            auto label = this->Y_.at(i);
            auto distance = euclidean_distance(current, sample);
            distances.emplace_back(distance, label);
        }
        std::sort(distances.begin(), distances.end());
        for (int i = 0; i < k; i++) {
            auto label = distances.at(i).second;
            neighbors.push_back(label);
        }
        std::unordered_map<int, int> frequency;
        for (auto neighbor : neighbors) {
            ++frequency[neighbor];
        }
        std::pair<int, int> predicted;
        predicted.first = -1;
        predicted.second = -1;
        for (auto& kv : frequency) {
            if (kv.second > predicted.second) {
                predicted.second = kv.second;
                predicted.first = kv.first;
            }
        }
        return predicted.first;
    }
};
}
}


static void test() {
    std::cout << "------- Test 1 -------" << std::endl;
    std::vector<std::vector<double>> X1 = {{0.0, 0.0}, {0.25, 0.25},
                                           {0.0, 0.5}, {0.5, 0.5},
                                           {1.0, 0.5}, {1.0, 1.0}};
    std::vector<int> Y1 = {1, 1, 1, 1, 2, 2};
    auto model1 = machine_learning::k_nearest_neighbors::Knn(X1, Y1);
    std::vector<double> sample1 = {1.2, 1.2};
    std::vector<double> sample2 = {0.1, 0.1};
    std::vector<double> sample3 = {0.1, 0.5};
    std::vector<double> sample4 = {1.0, 0.75};
    assert(model1.predict(sample1, 2) == 2);
    assert(model1.predict(sample2, 2) == 1);
    assert(model1.predict(sample3, 2) == 1);
    assert(model1.predict(sample4, 2) == 2);
    std::cout << "... Passed" << std::endl;
    std::cout << "------- Test 2 -------" << std::endl;
    std::vector<std::vector<double>> X2 = {
        {0.0, 0.0, 0.0}, {0.25, 0.25, 0.0}, {0.0, 0.5, 0.0}, {0.5, 0.5, 0.0},
        {1.0, 0.5, 0.0}, {1.0, 1.0, 0.0},   {1.0, 1.0, 1.0}, {1.5, 1.5, 1.0}};
    std::vector<int> Y2 = {1, 1, 1, 1, 2, 2, 3, 3};
    auto model2 = machine_learning::k_nearest_neighbors::Knn(X2, Y2);
    std::vector<double> sample5 = {1.2, 1.2, 0.0};
    std::vector<double> sample6 = {0.1, 0.1, 0.0};
    std::vector<double> sample7 = {0.1, 0.5, 0.0};
    std::vector<double> sample8 = {1.0, 0.75, 1.0};
    assert(model2.predict(sample5, 2) == 2);
    assert(model2.predict(sample6, 2) == 1);
    assert(model2.predict(sample7, 2) == 1);
    assert(model2.predict(sample8, 2) == 3);
    std::cout << "... Passed" << std::endl;
    std::cout << "------- Test 3 -------" << std::endl;
    std::vector<std::vector<double>> X3 = {{0.0}, {1.0}, {2.0}, {3.0},
                                           {4.0}, {5.0}, {6.0}, {7.0}};
    std::vector<int> Y3 = {1, 1, 1, 1, 2, 2, 2, 2};
    auto model3 = machine_learning::k_nearest_neighbors::Knn(X3, Y3);
    std::vector<double> sample9 = {0.5};
    std::vector<double> sample10 = {2.9};
    std::vector<double> sample11 = {5.5};
    std::vector<double> sample12 = {7.5};
    assert(model3.predict(sample9, 3) == 1);
    assert(model3.predict(sample10, 3) == 1);
    assert(model3.predict(sample11, 3) == 2);
    assert(model3.predict(sample12, 3) == 2);
    std::cout << "... Passed" << std::endl;
}


int main(int argc, char* argv[]) {
    test();
    return 0;
}
