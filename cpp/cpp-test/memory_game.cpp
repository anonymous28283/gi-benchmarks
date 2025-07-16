












template <typename T>
constexpr typename std::enable_if<std::is_integral<T>::value, void>::type SLEEP(
    T milliseconds) {
    Sleep(milliseconds * 1000);
}


template <typename T>
constexpr T SLEEP(T seconds) {
    return sleep(seconds);
}



namespace games {

namespace memory_game {

template <typename T>
bool is_number(const T &input) {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(256, '\n');

        return false;
    }

    return true;
}


template <typename T>
void init(std::vector<T> *table) {
    std::vector<char> letters(7);


    if ((*table).size() == 10) {
        letters = {'A', 'E', 'Z', 'P', 'D'};
    } else if ((*table).size() == 8) {
        letters = {'A', 'E', 'Z', 'D'};
    } else if ((*table).size() == 14) {
        letters = {'A', 'E', 'Z', 'P', 'D', 'B', 'M'};
    }

    std::vector<char> pairs;
    for (char letter : letters) {
        pairs.push_back(letter);
        pairs.push_back(letter);
    }

    std::shuffle(pairs.begin(), pairs.end(),
                 std::mt19937(std::random_device()()));

    for (int i = 0; i < (*table).size(); i++) {
        (*table)[i] = pairs[i];
    }

    std::cout << "All available types are: ";

    for (int i = 0; i < letters.size(); i++) {
        if (i == letters.size() - 1) {
            std::cout << "and " << letters[i] << ".\n\n";
        } else {
            std::cout << letters[i] << ", ";
        }
    }
}


template <typename T>
void print_table(const std::vector<T> &table) {
    std::cout << "| ";
    std::vector<T> table_print(table.size());

    for (int i = 0; i < table.size(); i++) {
        table_print[i] = ' ';

        if (table[i] != 0) {
            table_print[i] = table[i];
        }
    }

    for (int i = 0; i < table.size(); i++) {
        if (i % 5 == 0 && i != 0) {
            std::cout << "\n| ";
        }

        std::cout << table_print[i] << " | ";
    }
}



template <typename T>
void reset_data(const std::vector<T> &, int *, int *, int *);


template <typename T>
void ask_data(const std::vector<T> &table, int *answer, int *old_answer,
              int *memory_count) {
    (*old_answer) = (*answer);
    print_table(table);

    std::cout << "\n\nType your response here (number index):\n";
    std::cin >> (*answer);

    if (!is_number((*answer))) {
        std::cout << "\nYou must enter a valid number.\n\n";
        reset_data(table, answer, old_answer, memory_count);
    }



    (*memory_count)++;

    if (((*answer) > table.size()) || ((*answer) < 1)) {
        std::cout << "\nYou can't check a value that doesn't exist (or an "
                     "invalid number).\n\n";
        reset_data(table, answer, old_answer, memory_count);
    }

    if ((*old_answer) == (*answer)) {
        std::cout << "\nYou can't check the same value twice.\n\n";
        reset_data(table, answer, old_answer, memory_count);
    }




    if ((table[(*answer) - 1] != 0) &&
        ((table[(*old_answer)] == 0) || (table[(*old_answer)] != 0))) {
        std::cout << "\nYou can't check the same value twice.\n\n";
        reset_data(table, answer, old_answer, memory_count);
    }
}


template <typename T>
void reset_data(const std::vector<T> &table, int *answer, int *old_answer,
                int *memory_count) {
    (*answer) = (*old_answer);
    (*memory_count)--;

    ask_data(table, answer, old_answer, memory_count);
}


template <typename T>
bool match(const std::vector<T> &table, std::vector<T> *table_empty,
           const int &answer, bool *first_time, int *old_answer,
           int *memory_count) {
    if ((*first_time) == true) {
        return true;
    }



    for (int i = 0; i < table.size() + 1; i++) {
        if (i == answer) {
            if (table[i - 1] == table[(*old_answer) - 1]) {
                (*first_time) = true;
                (*memory_count) = 0;

                (*old_answer) = 0;
                return true;
            } else {
                std::cout << "\nNo match (value was " << table[i - 1]
                          << ", index is " << i << ").\n\n";

                (*table_empty)[(*old_answer) - 1] = 0;
                (*table_empty)[answer - 1] = 0;

                (*first_time) = true;
                (*memory_count) = 0;

                (*old_answer) = 0;
                return false;
            }
        }
    }

    return false;
}


template <typename T>
void assign_results(std::vector<T> *table_empty, std::vector<T> *table,
                    int *answer, bool *first_time, int *old_answer,
                    int *memory_count) {



    for (int i = 0; i < (*table).size() + 1; i++) {
        if (i == (*answer)) {
            if (match((*table), table_empty, (*answer), first_time, old_answer,
                      memory_count) == true) {
                (*table_empty)[i - 1] = (*table)[i - 1];
                (*first_time) = true;
            }
        }
    }

    if ((*memory_count) == 1) {
        (*first_time) = false;
        (*memory_count) = 0;
    }

    char try_again = 'n';



    for (int i = 0; i < (*table).size() + 1; i++) {
        if ((*table_empty)[i] == 0) {
            break;
        } else if (i == (*table).size() - 1) {
            print_table((*table));

            std::cout << "\n\nYou won. Congratulations! Do you want to play "
                         "again? (y/n)\n";
            std::cout
                << "Size " << (*table).size()
                << " will be used. This can be changed by re-running the game.";
            std::cin >> try_again;
            if (try_again == 'y') {


                for (int i = 0; i < (*table_empty).size(); i++) {
                    (*table_empty)[i] = 0;
                }

                init(table);
            } else if (try_again == 'n') {
                std::cout << "\nThanks for playing the game!\n";
                SLEEP(3);

                exit(0);
            } else {
                std::cout << "\nInvalid input (exitting...).\n";
                SLEEP(3);

                exit(0);
            }
        }
    }


    ask_data((*table_empty), answer, old_answer, memory_count);
    assign_results(table_empty, table, answer, first_time, old_answer,
                   memory_count);
}
}
}


int main() {

    std::srand(std::time(nullptr));

    int size = 0;
    int selection = 0;

    int response = 0;
    int old_answer = 0;

    int memory_count =
        0;
    bool first_time = true;


    std::cout << "\tMEMORY GAME\n";

    do {
        std::cout << "\n1. 4x2 (1)";
        std::cout << "\n2. 5x2 (2)";
        std::cout << "\n3. 7x2 (3)\n";

        std::cout << "\nChoose table size: ";
        std::cin >> selection;
    } while ((selection < 1 || selection > 3) &&
             (!games::memory_game::is_number(selection)));

    switch (selection) {
        case 1:
            size = 8;
            break;
        case 2:
            size = 10;
            break;
        case 3:
            size = 14;
            break;
        default:
            size = 10;
            break;
    }

    std::vector<char> table(size);
    std::vector<char> table_empty(size);

    std::cout << "\n";

    games::memory_game::init(&table);
    games::memory_game::ask_data(table_empty, &response, &old_answer,
                                 &memory_count);
    games::memory_game::assign_results(&table_empty, &table, &response,
                                       &first_time, &old_answer, &memory_count);

    return 0;
}
