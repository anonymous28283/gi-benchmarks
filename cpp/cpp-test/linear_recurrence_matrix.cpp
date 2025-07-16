






namespace math {

namespace linear_recurrence_matrix {

template <typename T = int64_t>
std::vector<std::vector<T>> matrix_multiplication(
    const std::vector<std::vector<T>>& _mat_a,
    const std::vector<std::vector<T>>& _mat_b, const int64_t mod = 1000000007) {

    assert(_mat_a[0].size() == _mat_b.size());
    std::vector<std::vector<T>> _mat_c(_mat_a.size(),
                                       std::vector<T>(_mat_b[0].size(), 0));

    for (uint32_t i = 0; i < _mat_a.size(); ++i) {
        for (uint32_t j = 0; j < _mat_b[0].size(); ++j) {
            for (uint32_t k = 0; k < _mat_b.size(); ++k) {
                _mat_c[i][j] =
                    (_mat_c[i][j] % mod +
                     (_mat_a[i][k] % mod * _mat_b[k][j] % mod) % mod) %
                    mod;
            }
        }
    }
    return _mat_c;
}

template <typename T = int64_t>
bool is_zero_matrix(const std::vector<std::vector<T>>& _mat) {
    for (uint32_t i = 0; i < _mat.size(); ++i) {
        for (uint32_t j = 0; j < _mat[i].size(); ++j) {
            if (_mat[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}


template <typename T = int64_t>
std::vector<std::vector<T>> matrix_exponentiation(
    std::vector<std::vector<T>> _mat, uint64_t power,
    const int64_t mod = 1000000007) {

    if (is_zero_matrix(_mat)) {
        return _mat;
    }

    std::vector<std::vector<T>> _mat_answer(_mat.size(),
                                            std::vector<T>(_mat.size(), 0));

    for (uint32_t i = 0; i < _mat.size(); ++i) {
        _mat_answer[i][i] = 1;
    }

    while (power > 0) {
        if (power & 1) {
            _mat_answer = matrix_multiplication(_mat_answer, _mat, mod);
        }
        power >>= 1;
        _mat = matrix_multiplication(_mat, _mat, mod);
    }

    return _mat_answer;
}


template <typename T = int64_t>
T get_nth_term_of_recurrence_series(
    const std::vector<std::vector<T>>& _mat,
    const std::vector<std::vector<T>>& _base_cases, uint64_t nth_term,
    bool constant_or_sum_included = false) {
    assert(_mat.size() == _base_cases.back().size());



    if (nth_term < _base_cases.back().size() - constant_or_sum_included) {
        return _base_cases.back()[nth_term - constant_or_sum_included];
    } else {

        std::vector<std::vector<T>> _res_matrix =
            matrix_exponentiation(_mat, nth_term - _base_cases.back().size() +
                                            1 + constant_or_sum_included);


        std::vector<std::vector<T>> _res =
            matrix_multiplication(_base_cases, _res_matrix);

        return _res.back().back();
    }
}
}
}


static void test() {

    std::vector<std::vector<int64_t>> fibonacci_matrix = {{0, 1}, {1, 1}},
                                      fib_base_case = {{0, 1}};

    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               fibonacci_matrix, fib_base_case, 11) == 89LL);
    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               fibonacci_matrix, fib_base_case, 39) == 63245986LL);


    std::vector<std::vector<int64_t>> tribonacci = {{0, 0, 1},
                                                    {1, 0, 1},
                                                    {0, 1, 1}},
                                      trib_base_case = {
                                          {0, 0, 1}};

    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               tribonacci, trib_base_case, 11) == 149LL);
    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               tribonacci, trib_base_case, 36) == 615693474LL);



    std::vector<std::vector<int64_t>> pell_recurrence = {{0, 1}, {1, 2}},
                                      pell_base_case = {
                                          {2, 2}};

    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               pell_recurrence, pell_base_case, 15) == 551614LL);
    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               pell_recurrence, pell_base_case, 23) == 636562078LL);



    std::vector<std::vector<int64_t>>
        custom_recurrence = {{1, 0, 1}, {0, 0, 1}, {0, 1, 2}},
        custom_base_case = {{7, 2, 2}};

    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               custom_recurrence, custom_base_case, 10, 1) == 18493LL);
    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               custom_recurrence, custom_base_case, 19, 1) == 51531251LL);



    std::vector<std::vector<int64_t>> sum_fibo_recurrence = {{0, 1, 1},
                                                             {1, 1, 1},
                                                             {0, 0, 1}},
                                      sum_fibo_base_case = {
                                          {0, 1, 1}};

    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               sum_fibo_recurrence, sum_fibo_base_case, 13, 1) == 609LL);
    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               sum_fibo_recurrence, sum_fibo_base_case, 16, 1) == 2583LL);


    std::vector<std::vector<int64_t>> tribonacci_sum = {{0, 0, 1, 1},
                                                        {1, 0, 1, 1},
                                                        {0, 1, 1, 1},
                                                        {0, 0, 0, 1}},
                                      trib_sum_base_case = {{0, 0, 1, 1}};


    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               tribonacci_sum, trib_sum_base_case, 18, 1) == 23249LL);
    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               tribonacci_sum, trib_sum_base_case, 19, 1) == 42762LL);
}


int main() {
    test();
    return 0;
}
