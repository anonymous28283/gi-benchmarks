







namespace divide_and_conquer {


namespace strassens_multiplication {


constexpr size_t MAX_SIZE = ~0ULL;

template <typename T,
          typename = typename std::enable_if<
              std::is_integral<T>::value || std::is_floating_point<T>::value,
              bool>::type>
class Matrix {
    std::vector<std::vector<T>> _mat;

 public:

    template <typename Integer,
              typename = typename std::enable_if<
                  std::is_integral<Integer>::value, Integer>::type>
    explicit Matrix(const Integer size) {
        for (size_t i = 0; i < size; ++i) {
            _mat.emplace_back(std::vector<T>(size, 0));
        }
    }


    template <typename Integer,
              typename = typename std::enable_if<
                  std::is_integral<Integer>::value, Integer>::type>
    Matrix(const Integer rows, const Integer cols) {
        for (size_t i = 0; i < rows; ++i) {
            _mat.emplace_back(std::vector<T>(cols, 0));
        }
    }


    inline std::pair<size_t, size_t> size() const {
        return {_mat.size(), _mat[0].size()};
    }


    template <typename Integer,
              typename = typename std::enable_if<
                  std::is_integral<Integer>::value, Integer>::type>
    inline std::vector<T> &operator[](const Integer index) {
        return _mat[index];
    }


    Matrix slice(const size_t row_start, const size_t row_end = MAX_SIZE,
                 const size_t col_start = MAX_SIZE,
                 const size_t col_end = MAX_SIZE) const {
        const size_t h_size =
            (row_end != MAX_SIZE ? row_end : _mat.size()) - row_start;
        const size_t v_size = (col_end != MAX_SIZE ? col_end : _mat[0].size()) -
                              (col_start != MAX_SIZE ? col_start : 0);
        Matrix result = Matrix<T>(h_size, v_size);

        const size_t v_start = (col_start != MAX_SIZE ? col_start : 0);
        for (size_t i = 0; i < h_size; ++i) {
            for (size_t j = 0; j < v_size; ++j) {
                result._mat[i][j] = _mat[i + row_start][j + v_start];
            }
        }
        return result;
    }


    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   Number>::type>
    void h_stack(const Matrix<Number> &other) {
        assert(_mat.size() == other._mat.size());
        for (size_t i = 0; i < other._mat.size(); ++i) {
            for (size_t j = 0; j < other._mat[i].size(); ++j) {
                _mat[i].push_back(other._mat[i][j]);
            }
        }
    }


    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   Number>::type>
    void v_stack(const Matrix<Number> &other) {
        assert(_mat[0].size() == other._mat[0].size());
        for (size_t i = 0; i < other._mat.size(); ++i) {
            _mat.emplace_back(std::vector<T>(other._mat[i].size()));
            for (size_t j = 0; j < other._mat[i].size(); ++j) {
                _mat.back()[j] = other._mat[i][j];
            }
        }
    }


    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    Matrix operator+(const Matrix<Number> &other) const {
        assert(this->size() == other.size());
        Matrix C = Matrix<Number>(_mat.size(), _mat[0].size());
        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < _mat[i].size(); ++j) {
                C._mat[i][j] = _mat[i][j] + other._mat[i][j];
            }
        }
        return C;
    }


    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    Matrix &operator+=(const Matrix<Number> &other) const {
        assert(this->size() == other.size());
        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < _mat[i].size(); ++j) {
                _mat[i][j] += other._mat[i][j];
            }
        }
        return this;
    }


    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    Matrix operator-(const Matrix<Number> &other) const {
        assert(this->size() == other.size());
        Matrix C = Matrix<Number>(_mat.size(), _mat[0].size());
        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < _mat[i].size(); ++j) {
                C._mat[i][j] = _mat[i][j] - other._mat[i][j];
            }
        }
        return C;
    }


    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    Matrix &operator-=(const Matrix<Number> &other) const {
        assert(this->size() == other.size());
        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < _mat[i].size(); ++j) {
                _mat[i][j] -= other._mat[i][j];
            }
        }
        return this;
    }


    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    inline Matrix operator*(const Matrix<Number> &other) const {
        assert(_mat[0].size() == other._mat.size());
        auto size = this->size();
        const size_t row = size.first, col = size.second;



        return (row == col && (row & 1) == 0)
                   ? this->strassens_multiplication(other)
                   : this->naive_multiplication(other);
    }


    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    inline Matrix operator*(const Number other) const {
        Matrix C = Matrix<Number>(_mat.size(), _mat[0].size());
        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < _mat[i].size(); ++j) {
                C._mat[i][j] = _mat[i][j] * other;
            }
        }
        return C;
    }


    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    Matrix &operator*=(const Number other) const {
        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < _mat[i].size(); ++j) {
                _mat[i][j] *= other;
            }
        }
        return this;
    }


    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    Matrix naive_multiplication(const Matrix<Number> &other) const {
        Matrix C = Matrix<Number>(_mat.size(), other._mat[0].size());

        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t k = 0; k < _mat[0].size(); ++k) {
                for (size_t j = 0; j < other._mat[0].size(); ++j) {
                    C._mat[i][j] += _mat[i][k] * other._mat[k][j];
                }
            }
        }
        return C;
    }


    template <typename Number, typename = typename std::enable_if<
                                   std::is_integral<Number>::value ||
                                       std::is_floating_point<Number>::value,
                                   bool>::type>
    Matrix strassens_multiplication(const Matrix<Number> &other) const {
        const size_t size = _mat.size();




        if (size <= 64ULL || (size & 1ULL)) {
            return this->naive_multiplication(other);
        } else {
            const Matrix<Number>
                A = this->slice(0ULL, size >> 1, 0ULL, size >> 1),
                B = this->slice(0ULL, size >> 1, size >> 1, size),
                C = this->slice(size >> 1, size, 0ULL, size >> 1),
                D = this->slice(size >> 1, size, size >> 1, size),
                E = other.slice(0ULL, size >> 1, 0ULL, size >> 1),
                F = other.slice(0ULL, size >> 1, size >> 1, size),
                G = other.slice(size >> 1, size, 0ULL, size >> 1),
                H = other.slice(size >> 1, size, size >> 1, size);

            Matrix P1 = A.strassens_multiplication(F - H);
            Matrix P2 = (A + B).strassens_multiplication(H);
            Matrix P3 = (C + D).strassens_multiplication(E);
            Matrix P4 = D.strassens_multiplication(G - E);
            Matrix P5 = (A + D).strassens_multiplication(E + H);
            Matrix P6 = (B - D).strassens_multiplication(G + H);
            Matrix P7 = (A - C).strassens_multiplication(E + F);









            Matrix C11 = P5 + P4 - P2 + P6;
            Matrix C12 = P1 + P2;
            Matrix C21 = P3 + P4;
            Matrix C22 = P1 + P5 - P3 - P7;

            C21.h_stack(C22);
            C11.h_stack(C12);
            C11.v_stack(C21);

            return C11;
        }
    }


    bool operator==(const Matrix<T> &other) const {
        if (_mat.size() != other._mat.size() ||
            _mat[0].size() != other._mat[0].size()) {
            return false;
        }
        for (size_t i = 0; i < _mat.size(); ++i) {
            for (size_t j = 0; j < _mat[i].size(); ++j) {
                if (_mat[i][j] != other._mat[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    friend std::ostream &operator<<(std::ostream &out, const Matrix<T> &mat) {
        for (auto &row : mat._mat) {
            for (auto &elem : row) {
                out << elem << " ";
            }
            out << "\n";
        }
        return out << "\n";
    }
};

}

}


static void test() {
    const size_t s = 512;
    auto matrix_demo =
        divide_and_conquer::strassens_multiplication::Matrix<size_t>(s, s);

    for (size_t i = 0; i < s; ++i) {
        for (size_t j = 0; j < s; ++j) {
            matrix_demo[i][j] = i + j;
        }
    }

    auto matrix_demo2 =
        divide_and_conquer::strassens_multiplication::Matrix<size_t>(s, s);
    for (size_t i = 0; i < s; ++i) {
        for (size_t j = 0; j < s; ++j) {
            matrix_demo2[i][j] = 2 + i + j;
        }
    }

    auto start = std::chrono::system_clock::now();
    auto Mat3 = matrix_demo2 * matrix_demo;
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> time = (end - start);
    std::cout << "Strassen time: " << time.count() << "s" << std::endl;

    start = std::chrono::system_clock::now();
    auto conf = matrix_demo2.naive_multiplication(matrix_demo);
    end = std::chrono::system_clock::now();

    time = end - start;
    std::cout << "Normal time: " << time.count() << "s" << std::endl;


    assert(Mat3 == conf);
}


int main() {
    test();
    return 0;
}
