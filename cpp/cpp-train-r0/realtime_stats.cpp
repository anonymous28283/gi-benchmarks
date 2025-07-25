





namespace statistics {


template <typename T>
class stats_computer1 {
 public:

    void new_val(T x) {
        if (n == 0)
            K = x;
        n++;
        T tmp = x - K;
        Ex += tmp;
        Ex2 += static_cast<double>(tmp) * tmp;
    }


    double mean() const { return K + Ex / n; }


    double variance() const { return (Ex2 - (Ex * Ex) / n) / (n - 1); }


    double std() const { return std::sqrt(this->variance()); }


    friend std::istream &operator>>(std::istream &input,
                                    stats_computer1 &stat) {
        T val;
        input >> val;
        stat.new_val(val);
        return input;
    }

 private:
    unsigned int n = 0;
    double Ex, Ex2;
    T K;
};


template <typename T>
class stats_computer2 {
 public:

    void new_val(T x) {
        n++;
        double delta = x - mu;
        mu += delta / n;
        double delta2 = x - mu;
        M += delta * delta2;
    }


    double mean() const { return mu; }


    double variance() const { return M / n; }


    double std() const { return std::sqrt(this->variance()); }


    friend std::istream &operator>>(std::istream &input,
                                    stats_computer2 &stat) {
        T val;
        input >> val;
        stat.new_val(val);
        return input;
    }

 private:
    unsigned int n = 0;
    double mu = 0, var = 0, M = 0;
};

}

using statistics::stats_computer1;
using statistics::stats_computer2;


void test_function(const float *test_data, const int number_of_samples) {
    float mean = 0.f, variance = 0.f;

    stats_computer1<float> stats01;
    stats_computer2<float> stats02;

    for (int i = 0; i < number_of_samples; i++) {
        stats01.new_val(test_data[i]);
        stats02.new_val(test_data[i]);
        mean += test_data[i];
    }

    mean /= number_of_samples;

    for (int i = 0; i < number_of_samples; i++) {
        float temp = test_data[i] - mean;
        variance += temp * temp;
    }
    variance /= number_of_samples;

    std::cout << "<<<<<<<< Test Function >>>>>>>>" << std::endl
              << "Expected: Mean: " << mean << "\t Variance: " << variance
              << std::endl;
    std::cout << "\tMethod 1:"
              << "\tMean: " << stats01.mean()
              << "\t Variance: " << stats01.variance()
              << "\t Std: " << stats01.std() << std::endl;
    std::cout << "\tMethod 2:"
              << "\tMean: " << stats02.mean()
              << "\t Variance: " << stats02.variance()
              << "\t Std: " << stats02.std() << std::endl;

    assert(std::abs(stats01.mean() - mean) < 0.01);
    assert(std::abs(stats02.mean() - mean) < 0.01);
    assert(std::abs(stats02.variance() - variance) < 0.01);

    std::cout << "(Tests passed)" << std::endl;
}


int main(int argc, char **argv) {
    const float test_data1[] = {3, 4, 5, -1.4, -3.6, 1.9, 1.};
    test_function(test_data1, sizeof(test_data1) / sizeof(test_data1[0]));

    std::cout
        << "Enter data. Any non-numeric data will terminate the data input."
        << std::endl;

    stats_computer1<float> stats1;
    stats_computer2<float> stats2;

    while (1) {
        double val;
        std::cout << "Enter number: ";
        std::cin >> val;



        if (std::cin.fail())
            break;

        stats1.new_val(val);
        stats2.new_val(val);

        std::cout << "\tMethod 1:"
                  << "\tMean: " << stats1.mean()
                  << "\t Variance: " << stats1.variance()
                  << "\t Std: " << stats1.std() << std::endl;
        std::cout << "\tMethod 2:"
                  << "\tMean: " << stats2.mean()
                  << "\t Variance: " << stats2.variance()
                  << "\t Std: " << stats2.std() << std::endl;
    }

    return 0;
}
