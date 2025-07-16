







namespace range_queries {

namespace sparse_table {

template <typename T>
std::vector<T> computeLogs(const std::vector<T>& A) {
    int n = A.size();
    std::vector<T> logs(n);
    logs[1] = 0;
    for (int i = 2; i < n; i++) {
        logs[i] = logs[i / 2] + 1;
    }
    return logs;
}


template <typename T>
std::vector<std::vector<T> > buildTable(const std::vector<T>& A,
                                        const std::vector<T>& logs) {
    int n = A.size();
    std::vector<std::vector<T> > table(20, std::vector<T>(n + 5, 0));
    int curLen = 0;
    for (int i = 0; i <= logs[n]; i++) {
        curLen = 1 << i;
        for (int j = 0; j + curLen < n; j++) {
            if (curLen == 1) {
                table[i][j] = A[j];
            } else {
                table[i][j] =
                    std::min(table[i - 1][j], table[i - 1][j + curLen / 2]);
            }
        }
    }
    return table;
}


template <typename T>
int getMinimum(int beg, int end, const std::vector<T>& logs,
               const std::vector<std::vector<T> >& table) {
    int p = logs[end - beg + 1];
    int pLen = 1 << p;
    return std::min(table[p][beg], table[p][end - pLen + 1]);
}
}
}


int main() {
    std::vector<int> A{1, 2, 0, 3, 9};
    std::vector<int> logs = range_queries::sparse_table::computeLogs(A);
    std::vector<std::vector<int> > table =
        range_queries::sparse_table::buildTable(A, logs);
    assert(range_queries::sparse_table::getMinimum(0, 0, logs, table) == 1);
    assert(range_queries::sparse_table::getMinimum(0, 4, logs, table) == 0);
    assert(range_queries::sparse_table::getMinimum(2, 4, logs, table) == 0);
    return 0;
}
