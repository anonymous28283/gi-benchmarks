















namespace machine_learning {

namespace neural_network {

namespace activations {

double sigmoid(const double &x) { return 1.0 / (1.0 + std::exp(-x)); }


double dsigmoid(const double &x) { return x * (1 - x); }


double relu(const double &x) { return std::max(0.0, x); }


double drelu(const double &x) { return x >= 0.0 ? 1.0 : 0.0; }


double tanh(const double &x) { return 2 / (1 + std::exp(-2 * x)) - 1; }


double dtanh(const double &x) { return 1 - x * x; }
}

namespace util_functions {

double square(const double &x) { return x * x; }

double identity_function(const double &x) { return x; }
}

namespace layers {

class DenseLayer {
 public:

    double (*activation_function)(const double &);
    double (*dactivation_function)(const double &);
    int neurons;
    std::string activation;
    std::vector<std::valarray<double>> kernel;


    DenseLayer(const int &neurons, const std::string &activation,
               const std::pair<size_t, size_t> &kernel_shape,
               const bool &random_kernel) {

        if (activation == "sigmoid") {
            activation_function = neural_network::activations::sigmoid;
            dactivation_function = neural_network::activations::sigmoid;
        } else if (activation == "relu") {
            activation_function = neural_network::activations::relu;
            dactivation_function = neural_network::activations::drelu;
        } else if (activation == "tanh") {
            activation_function = neural_network::activations::tanh;
            dactivation_function = neural_network::activations::dtanh;
        } else if (activation == "none") {

            activation_function =
                neural_network::util_functions::identity_function;
            dactivation_function =
                neural_network::util_functions::identity_function;
        } else {

            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "Invalid argument. Expected {none, sigmoid, relu, "
                         "tanh} got ";
            std::cerr << activation << std::endl;
            std::exit(EXIT_FAILURE);
        }
        this->activation = activation;
        this->neurons = neurons;

        if (random_kernel) {
            uniform_random_initialization(kernel, kernel_shape, -1.0, 1.0);
        } else {
            unit_matrix_initialization(kernel, kernel_shape);
        }
    }

    DenseLayer(const int &neurons, const std::string &activation,
               const std::vector<std::valarray<double>> &kernel) {

        if (activation == "sigmoid") {
            activation_function = neural_network::activations::sigmoid;
            dactivation_function = neural_network::activations::sigmoid;
        } else if (activation == "relu") {
            activation_function = neural_network::activations::relu;
            dactivation_function = neural_network::activations::drelu;
        } else if (activation == "tanh") {
            activation_function = neural_network::activations::tanh;
            dactivation_function = neural_network::activations::dtanh;
        } else if (activation == "none") {

            activation_function =
                neural_network::util_functions::identity_function;
            dactivation_function =
                neural_network::util_functions::identity_function;
        } else {

            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "Invalid argument. Expected {none, sigmoid, relu, "
                         "tanh} got ";
            std::cerr << activation << std::endl;
            std::exit(EXIT_FAILURE);
        }
        this->activation = activation;
        this->neurons = neurons;
        this->kernel = kernel;
    }


    DenseLayer(const DenseLayer &layer) = default;


    ~DenseLayer() = default;


    DenseLayer &operator=(const DenseLayer &layer) = default;


    DenseLayer(DenseLayer &&) = default;


    DenseLayer &operator=(DenseLayer &&) = default;
};
}

class NeuralNetwork {
 private:
    std::vector<neural_network::layers::DenseLayer> layers;

    NeuralNetwork(
        const std::vector<std::pair<int, std::string>> &config,
        const std::vector<std::vector<std::valarray<double>>> &kernels) {

        if (config.begin()->second != "none") {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr
                << "First layer can't have activation other than none got "
                << config.begin()->second;
            std::cerr << std::endl;
            std::exit(EXIT_FAILURE);
        }

        if (config.size() <= 1) {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "Invalid size of network, ";
            std::cerr << "Atleast two layers are required";
            std::exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < config.size(); i++) {
            layers.emplace_back(neural_network::layers::DenseLayer(
                config[i].first, config[i].second, kernels[i]));
        }
        std::cout << "INFO: Network constructed successfully" << std::endl;
    }

    std::vector<std::vector<std::valarray<double>>>
    __detailed_single_prediction(const std::vector<std::valarray<double>> &X) {
        std::vector<std::vector<std::valarray<double>>> details;
        std::vector<std::valarray<double>> current_pass = X;
        details.emplace_back(X);
        for (const auto &l : layers) {
            current_pass = multiply(current_pass, l.kernel);
            current_pass = apply_function(current_pass, l.activation_function);
            details.emplace_back(current_pass);
        }
        return details;
    }

 public:

    NeuralNetwork() = default;


    explicit NeuralNetwork(
        const std::vector<std::pair<int, std::string>> &config) {

        if (config.begin()->second != "none") {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr
                << "First layer can't have activation other than none got "
                << config.begin()->second;
            std::cerr << std::endl;
            std::exit(EXIT_FAILURE);
        }

        if (config.size() <= 1) {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "Invalid size of network, ";
            std::cerr << "Atleast two layers are required";
            std::exit(EXIT_FAILURE);
        }


        layers.push_back(neural_network::layers::DenseLayer(
            config[0].first, config[0].second,
            {config[0].first, config[0].first}, false));

        for (size_t i = 1; i < config.size(); i++) {
            layers.push_back(neural_network::layers::DenseLayer(
                config[i].first, config[i].second,
                {config[i - 1].first, config[i].first}, true));
        }
        std::cout << "INFO: Network constructed successfully" << std::endl;
    }


    NeuralNetwork(const NeuralNetwork &model) = default;


    ~NeuralNetwork() = default;


    NeuralNetwork &operator=(const NeuralNetwork &model) = default;


    NeuralNetwork(NeuralNetwork &&) = default;


    NeuralNetwork &operator=(NeuralNetwork &&) = default;


    std::pair<std::vector<std::vector<std::valarray<double>>>,
              std::vector<std::vector<std::valarray<double>>>>
    get_XY_from_csv(const std::string &file_name, const bool &last_label,
                    const bool &normalize, const int &slip_lines = 1) {
        std::ifstream in_file;
        in_file.open(file_name.c_str(), std::ios::in);

        if (!in_file.is_open()) {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "Unable to open file: " << file_name << std::endl;
            std::exit(EXIT_FAILURE);
        }
        std::vector<std::vector<std::valarray<double>>> X,
            Y;
        std::string line;

        for (int i = 0; i < slip_lines; i++) {
            std::getline(in_file, line, '\n');
        }

        while (!in_file.eof() && std::getline(in_file, line, '\n')) {
            std::valarray<double> x_data,
                y_data;
            std::stringstream ss(line);
            std::string token;
            while (std::getline(ss, token, ',')) {

                x_data = insert_element(x_data, std::stod(token));
            }

            if (last_label) {
                y_data.resize(this->layers.back().neurons);

                if (y_data.size() > 1) {
                    y_data[x_data[x_data.size() - 1]] = 1;
                }

                else {
                    y_data[0] = x_data[x_data.size() - 1];
                }
                x_data = pop_back(x_data);
            } else {
                y_data.resize(this->layers.back().neurons);

                if (y_data.size() > 1) {
                    y_data[x_data[x_data.size() - 1]] = 1;
                }

                else {
                    y_data[0] = x_data[x_data.size() - 1];
                }
                x_data = pop_front(x_data);
            }

            X.push_back({x_data});
            Y.push_back({y_data});
        }

        if (normalize) {

            X = minmax_scaler(X, 0.01, 1.0);
        }
        in_file.close();
        return make_pair(X, Y);
    }


    std::vector<std::valarray<double>> single_predict(
        const std::vector<std::valarray<double>> &X) {

        auto activations = this->__detailed_single_prediction(X);

        return activations.back();
    }


    std::vector<std::vector<std::valarray<double>>> batch_predict(
        const std::vector<std::vector<std::valarray<double>>> &X) {

        std::vector<std::vector<std::valarray<double>>> predicted_batch(
            X.size());
        for (size_t i = 0; i < X.size(); i++) {

            predicted_batch[i] = this->single_predict(X[i]);
        }
        return predicted_batch;
    }


    void fit(const std::vector<std::vector<std::valarray<double>>> &X_,
             const std::vector<std::vector<std::valarray<double>>> &Y_,
             const int &epochs = 100, const double &learning_rate = 0.01,
             const size_t &batch_size = 32, const bool &shuffle = true) {
        std::vector<std::vector<std::valarray<double>>> X = X_, Y = Y_;

        if (X.size() != Y.size()) {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "X and Y in fit have different sizes" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        std::cout << "INFO: Training Started" << std::endl;
        for (int epoch = 1; epoch <= epochs; epoch++) {

            if (shuffle) {
                equal_shuffle(X, Y);
            }
            auto start =
                std::chrono::high_resolution_clock::now();
            double loss = 0,
                   acc = 0;

            for (size_t batch_start = 0; batch_start < X.size();
                 batch_start += batch_size) {
                for (size_t i = batch_start;
                     i < std::min(X.size(), batch_start + batch_size); i++) {
                    std::vector<std::valarray<double>> grad, cur_error,
                        predicted;
                    auto activations = this->__detailed_single_prediction(X[i]);


                    std::vector<std::vector<std::valarray<double>>> gradients;
                    gradients.resize(this->layers.size());

                    for (size_t i = 0; i < gradients.size(); i++) {
                        zeroes_initialization(
                            gradients[i], get_shape(this->layers[i].kernel));
                    }
                    predicted = activations.back();
                    cur_error = predicted - Y[i];

                    loss += sum(apply_function(
                        cur_error, neural_network::util_functions::square));

                    if (argmax(predicted) == argmax(Y[i])) {
                        acc += 1;
                    }

                    for (size_t j = this->layers.size() - 1; j >= 1; j--) {

                        cur_error = hadamard_product(
                            cur_error,
                            apply_function(
                                activations[j + 1],
                                this->layers[j].dactivation_function));

                        grad = multiply(transpose(activations[j]), cur_error);

                        cur_error = multiply(cur_error,
                                             transpose(this->layers[j].kernel));

                        gradients[j] = gradients[j] + grad / double(batch_size);
                    }

                    for (size_t j = this->layers.size() - 1; j >= 1; j--) {

                        this->layers[j].kernel = this->layers[j].kernel -
                                                 gradients[j] * learning_rate;
                    }
                }
            }
            auto stop =
                std::chrono::high_resolution_clock::now();

            auto duration =
                std::chrono::duration_cast<std::chrono::microseconds>(stop -
                                                                      start);
            loss /= X.size();
            acc /= X.size();
            std::cout.precision(4);

            std::cout << "Training: Epoch " << epoch << '/' << epochs;
            std::cout << ", Loss: " << loss;
            std::cout << ", Accuracy: " << acc;
            std::cout << ", Taken time: " << duration.count() / 1e6
                      << " seconds";
            std::cout << std::endl;
        }
        return;
    }


    void fit_from_csv(const std::string &file_name, const bool &last_label,
                      const int &epochs, const double &learning_rate,
                      const bool &normalize, const int &slip_lines = 1,
                      const size_t &batch_size = 32,
                      const bool &shuffle = true) {

        auto data =
            this->get_XY_from_csv(file_name, last_label, normalize, slip_lines);

        this->fit(data.first, data.second, epochs, learning_rate, batch_size,
                  shuffle);
        return;
    }


    void evaluate(const std::vector<std::vector<std::valarray<double>>> &X,
                  const std::vector<std::vector<std::valarray<double>>> &Y) {
        std::cout << "INFO: Evaluation Started" << std::endl;
        double acc = 0, loss = 0;
        for (size_t i = 0; i < X.size(); i++) {

            std::vector<std::valarray<double>> pred =
                this->single_predict(X[i]);

            if (argmax(pred) == argmax(Y[i])) {
                acc += 1;
            }

            loss += sum(apply_function((Y[i] - pred),
                                       neural_network::util_functions::square) *
                        0.5);
        }
        acc /= X.size();
        loss /= X.size();

        std::cout << "Evaluation: Loss: " << loss;
        std::cout << ", Accuracy: " << acc << std::endl;
        return;
    }


    void evaluate_from_csv(const std::string &file_name, const bool &last_label,
                           const bool &normalize, const int &slip_lines = 1) {

        auto data =
            this->get_XY_from_csv(file_name, last_label, normalize, slip_lines);

        this->evaluate(data.first, data.second);
        return;
    }


    void save_model(const std::string &_file_name) {
        std::string file_name = _file_name;

        if (file_name.find(".model") == file_name.npos) {
            file_name += ".model";
        }
        std::ofstream out_file;

        out_file.open(file_name.c_str(),
                      std::ofstream::out | std::ofstream::trunc);

        if (!out_file.is_open()) {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "Unable to open file: " << file_name << std::endl;
            std::exit(EXIT_FAILURE);
        }


        out_file << layers.size();
        out_file << std::endl;
        for (const auto &layer : this->layers) {
            out_file << layer.neurons << ' ' << layer.activation << std::endl;
            const auto shape = get_shape(layer.kernel);
            out_file << shape.first << ' ' << shape.second << std::endl;
            for (const auto &row : layer.kernel) {
                for (const auto &val : row) {
                    out_file << val << ' ';
                }
                out_file << std::endl;
            }
        }
        std::cout << "INFO: Model saved successfully with name : ";
        std::cout << file_name << std::endl;
        out_file.close();
        return;
    }


    NeuralNetwork load_model(const std::string &file_name) {
        std::ifstream in_file;
        in_file.open(file_name.c_str());

        if (!in_file.is_open()) {
            std::cerr << "ERROR (" << __func__ << ") : ";
            std::cerr << "Unable to open file: " << file_name << std::endl;
            std::exit(EXIT_FAILURE);
        }
        std::vector<std::pair<int, std::string>> config;
        std::vector<std::vector<std::valarray<double>>>
            kernels;

        size_t total_layers = 0;
        in_file >> total_layers;
        for (size_t i = 0; i < total_layers; i++) {
            int neurons = 0;
            std::string activation;
            size_t shape_a = 0, shape_b = 0;
            std::vector<std::valarray<double>> kernel;
            in_file >> neurons >> activation >> shape_a >> shape_b;
            for (size_t r = 0; r < shape_a; r++) {
                std::valarray<double> row(shape_b);
                for (size_t c = 0; c < shape_b; c++) {
                    in_file >> row[c];
                }
                kernel.push_back(row);
            }
            config.emplace_back(make_pair(neurons, activation));
            ;
            kernels.emplace_back(kernel);
        }
        std::cout << "INFO: Model loaded successfully" << std::endl;
        in_file.close();
        return NeuralNetwork(
            config, kernels);
    }


    void summary() {

        std::cout
            << "==============================================================="
            << std::endl;
        std::cout << "\t\t+ MODEL SUMMARY +\t\t\n";
        std::cout
            << "==============================================================="
            << std::endl;
        for (size_t i = 1; i <= layers.size(); i++) {
            std::cout << i << ")";
            std::cout << " Neurons : "
                      << layers[i - 1].neurons;
            std::cout << ", Activation : "
                      << layers[i - 1].activation;
            std::cout << ", kernel Shape : "
                      << get_shape(layers[i - 1].kernel);
            std::cout << std::endl;
        }
        std::cout
            << "==============================================================="
            << std::endl;
        return;
    }
};
}
}


static void test() {

    machine_learning::neural_network::NeuralNetwork myNN =
        machine_learning::neural_network::NeuralNetwork({
            {4, "none"},
            {6,
             "relu"},
            {3, "sigmoid"}

        });

    myNN.summary();

    myNN.fit_from_csv("iris.csv", true, 100, 0.3, false, 2, 32, true);

    assert(machine_learning::argmax(
               myNN.single_predict({{5, 3.4, 1.6, 0.4}})) == 0);
    assert(machine_learning::argmax(
               myNN.single_predict({{6.4, 2.9, 4.3, 1.3}})) == 1);
    assert(machine_learning::argmax(
               myNN.single_predict({{6.2, 3.4, 5.4, 2.3}})) == 2);
    return;
}


int main() {

    test();
    return 0;
}
