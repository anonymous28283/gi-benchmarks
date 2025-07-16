










using std::cin;
using std::cout;
using std::endl;
using std::get;
using std::left;
using std::make_tuple;
using std::priority_queue;
using std::tuple;
using std::unordered_set;
using std::vector;


template <typename S, typename T, typename E>
bool sortcol(tuple<S, T, E>& t1, tuple<S, T, E>& t2) {
    if (get<1>(t1) < get<1>(t2) ||
        (get<1>(t1) == get<1>(t2) && get<0>(t1) < get<0>(t2))) {
        return true;
    }
    return false;
}


template <typename S, typename T, typename E>
class Compare {
 public:

    bool operator()(tuple<S, T, E, double, double, double>& t1,
                    tuple<S, T, E, double, double, double>& t2) {

        if (get<2>(t2) < get<2>(t1)) {
            return true;
        }

        else if (get<2>(t2) == get<2>(t1)) {
            return get<1>(t2) < get<1>(t1);
        }
        return false;
    }
};


template <typename S, typename T, typename E>
class SJF {

    priority_queue<tuple<S, T, E, double, double, double>,
                   vector<tuple<S, T, E, double, double, double>>,
                   Compare<S, T, E>>
        schedule;


    vector<tuple<S, T, E, double, double, double>> result;


    unordered_set<S> idList;

 public:

    void addProcess(S id, T arrival, E burst) {

        if (idList.find(id) == idList.end()) {
            tuple<S, T, E, double, double, double> t =
                make_tuple(id, arrival, burst, 0, 0, 0);
            schedule.push(t);
            idList.insert(id);
        }
    }



    vector<tuple<S, T, E, double, double, double>> scheduleForSJF() {

        double timeElapsed = 0;

        while (!schedule.empty()) {
            tuple<S, T, E, double, double, double> cur = schedule.top();



            if (get<1>(cur) > timeElapsed) {
                timeElapsed += get<1>(cur) - timeElapsed;
            }


            timeElapsed += get<2>(cur);



            get<3>(cur) = timeElapsed;


            get<4>(cur) = get<3>(cur) - get<1>(cur);


            get<5>(cur) = get<4>(cur) - get<2>(cur);


            assert(get<4>(cur) >= get<2>(cur));


            assert(get<5>(cur) >= 0);

            result.push_back(cur);
            schedule.pop();
        }
        return result;
    }


    void printResult(
        const vector<tuple<S, T, E, double, double, double>>& processes) {
        cout << std::setw(17) << left << "Process ID" << std::setw(17) << left
             << "Arrival Time" << std::setw(17) << left << "Burst Time"
             << std::setw(17) << left << "Completion Time" << std::setw(17)
             << left << "Turnaround Time" << std::setw(17) << left
             << "Waiting Time" << endl;

        for (const auto& process : processes) {
            cout << std::setprecision(2) << std::fixed << std::setw(17) << left
                 << get<0>(process) << std::setw(17) << left << get<1>(process)
                 << std::setw(17) << left << get<2>(process) << std::setw(17)
                 << left << get<3>(process) << std::setw(17) << left
                 << get<4>(process) << std::setw(17) << left << get<5>(process)
                 << endl;
        }
    }
};


template <typename S, typename T, typename E>
vector<tuple<S, T, E, double, double, double>> get_final_status(
    vector<tuple<S, T, E>> input) {

    sort(input.begin(), input.end(), sortcol<S, T, E>);


    vector<tuple<S, T, E, double, double, double>> result(input.size());
    double timeElapsed = 0;

    for (size_t i = 0; i < input.size(); i++) {

        T arrival = get<1>(input[i]);
        E burst = get<2>(input[i]);


        if (arrival > timeElapsed) {
            timeElapsed = arrival;
        }


        timeElapsed += burst;


        double completion = timeElapsed;
        double turnaround = completion - arrival;
        double waiting = turnaround - burst;


        result[i] = make_tuple(get<0>(input[i]), arrival, burst, completion,
                               turnaround, waiting);
    }

    return result;
}


static void test() {

    vector<tuple<uint32_t, uint32_t, uint32_t, double, double, double>>
        finalResult;

    for (int i{}; i < 10; i++) {
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<> distr(1, 10);

        uint32_t n = distr(eng);
        SJF<uint32_t, uint32_t, uint32_t> readyQueue;
        vector<tuple<uint32_t, uint32_t, uint32_t, double, double, double>>
            input(n);


        for (uint32_t i{}; i < n; i++) {
            get<0>(input[i]) = i;
            get<1>(input[i]) = distr(eng);
            get<2>(input[i]) = distr(eng);
        }


        cout << "Processes before SJF scheduling:" << endl;
        readyQueue.printResult(input);


        for (uint32_t i{}; i < n; i++) {
            readyQueue.addProcess(get<0>(input[i]), get<1>(input[i]),
                                  get<2>(input[i]));
        }


        auto finalResult = readyQueue.scheduleForSJF();


        cout << "\nProcesses after SJF scheduling:" << endl;
        readyQueue.printResult(finalResult);
    }
    cout << "All the tests have successfully passed!" << endl;
}


int main() {
    test();
    return 0;
}
