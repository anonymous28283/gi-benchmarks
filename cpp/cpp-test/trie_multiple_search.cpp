










namespace operations_on_datastructures {

namespace trie_operations {

class Tnode {
 private:
    static constexpr uint8_t ENGLISH_ALPHABET_SIZE = 26;

    std::vector<Tnode *> english;


    bool endOfWord;


    uint32_t frequency;

 public:
    Tnode() {
        english.resize(ENGLISH_ALPHABET_SIZE, nullptr);
        endOfWord = false;
        frequency = 0;
    }

    Tnode(const Tnode &node) {
        english = node.english;
        endOfWord = node.endOfWord;
        frequency = node.frequency;
    }

    Tnode &operator=(const Tnode &node) = default;

    Tnode(Tnode &&) = default;

    Tnode &operator=(Tnode &&) = default;

    inline uint8_t numberOfChildren(Tnode *node) {
        return ENGLISH_ALPHABET_SIZE -
               std::count(node->english.begin(), node->english.end(), nullptr);
    }


    void Insert(const std::string &entry);
    void Delete(std::string entry);
    void DeleteFrom(Tnode *delete_from, std::string delete_string,
                    int remove_index);
    bool SearchPresence(const std::string &key);
    void SuggestAutocomplete(Tnode *new_root, const std::string &prefix);
    void SearchSuggestions(const std::string &key);
    void SuggestFreqAutocomplete(
        Tnode *new_root, const std::string &prefix,
        std::priority_queue<std::pair<int, std::string> > *suggestions);
    void SearchFreqSuggestions(const std::string &key);
    void SelectionTop_3(
        std::priority_queue<std::pair<int, std::string> > *suggestions);


    ~Tnode() {
        int i = 0;
        for (i = 0; i < ENGLISH_ALPHABET_SIZE; i++) {
            if (english[i]) {
                delete english[i];
            }
        }
    }
};


void Tnode::Insert(const std::string &entry) {
    Tnode *cur_pos = this;
    int letter_index = 0;

    for (auto &i : entry) {

        letter_index = tolower(i) - 97;



        if (cur_pos->english[letter_index] == nullptr) {
            cur_pos->english[letter_index] = new Tnode();
        }

        cur_pos = cur_pos->english[letter_index];
    }

    cur_pos->endOfWord = true;
}


void Tnode::DeleteFrom(Tnode *delete_from, std::string delete_string,
                       int remove_index) {
    if (delete_string.size() == remove_index) {
        int letter_index = tolower(delete_string[remove_index]) - 97;

        DeleteFrom(delete_from->english[letter_index], delete_string,
                   remove_index + 1);

        delete delete_from;
    }
}


void Tnode::Delete(std::string entry) {
    Tnode *cur_pos = this,
          *delete_from = this;
    int letter_index = 0, delete_from_index = 0, i = 0, n = entry.size();

    for (i = 0; i < n; i++) {

        letter_index = tolower(entry[i]) - 97;


        if (cur_pos->english[letter_index] == nullptr) {
            std::cout << "Entry not Found" << std::endl;
            return;
        }



        if (numberOfChildren(cur_pos) > 1 || cur_pos->endOfWord) {
            delete_from = cur_pos;

            delete_from_index = i - 1;

        }


        cur_pos = cur_pos->english[letter_index];
    }



    if (!cur_pos->endOfWord) {
        std::cout << "Entry not Found" << std::endl;
        return;
    }



    if (numberOfChildren(cur_pos)) {
        cur_pos->endOfWord = false;
        cur_pos->frequency = 0;
        return;
    }


    letter_index = tolower(entry[delete_from_index + 1]) - 97;

    cur_pos = delete_from->english[letter_index];

    delete_from->english[letter_index] = nullptr;



    if (n > delete_from_index + 2) {
        DeleteFrom(cur_pos, entry, delete_from_index + 2);
    }

    else {
        delete cur_pos;
    }
}


bool Tnode::SearchPresence(const std::string &key) {
    Tnode *cur_pos = this;
    int letter_index = 0;

    for (auto &i : key) {
        letter_index = tolower(i) - 97;

        if (cur_pos->english[letter_index] == nullptr) {
            return false;
        }
        cur_pos = cur_pos->english[letter_index];
    }


    if (cur_pos->endOfWord) {
        (cur_pos->frequency)++;
        return true;
    } else {
        return false;
    }
}


void Tnode::SuggestAutocomplete(Tnode *new_root, const std::string &prefix) {


    int i = 0;
    for (i = 0; i < ENGLISH_ALPHABET_SIZE; i++) {
        if (new_root->english[i] != nullptr) {


            if (new_root->english[i]->endOfWord) {
                std::cout << prefix + char(i + 97) << std::endl;
            }

            SuggestAutocomplete(new_root->english[i], prefix + char(i + 97));
        }
    }
}


void Tnode::SearchSuggestions(const std::string &key) {
    Tnode *cur_pos = nullptr, *prev_pos = nullptr;
    cur_pos = prev_pos = this;
    int letter_index = 0;
    std::string prefix =
        "";

    for (auto &i : key) {
        letter_index = tolower(i) - 97;
        prev_pos = cur_pos;




        if (cur_pos->english[letter_index] == nullptr) {
            SuggestAutocomplete(prev_pos, prefix);
            std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - "
                      << std::endl;
            return;
        }

        prefix += char(tolower(i));
        cur_pos = cur_pos->english[letter_index];
    }

    if (cur_pos->endOfWord) {
        std::cout << key << std::endl;
        (cur_pos->frequency)++;
    }

    (void)prev_pos;



    SuggestAutocomplete(cur_pos, prefix);
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - "
              << std::endl;
    return;
}


void Tnode::SelectionTop_3(
    std::priority_queue<std::pair<int, std::string> > *suggestions) {

    int n = suggestions->size(), Top = 0;
    Top = n < 3 ? n : 3;
    while (Top--) {
        std::cout << suggestions->top().second << std::endl;
        suggestions->pop();
    }
}


void Tnode::SuggestFreqAutocomplete(
    Tnode *new_root, const std::string &prefix,
    std::priority_queue<std::pair<int, std::string> > *suggestions) {
    int i = 0;
    for (i = 0; i < ENGLISH_ALPHABET_SIZE; i++) {
        if (new_root->english[i] != nullptr) {


            if (new_root->english[i]->endOfWord) {
                suggestions->push(std::make_pair(
                    new_root->english[i]->frequency, prefix + char(i + 97)));
            }

            SuggestFreqAutocomplete(new_root->english[i], prefix + char(i + 97),
                                    suggestions);
        }
    }
}


void Tnode::SearchFreqSuggestions(const std::string &key) {
    Tnode *cur_pos = nullptr, *prev_pos = nullptr;
    cur_pos = prev_pos = this;
    int letter_index = 0;
    std::string prefix =
        "";
    std::priority_queue<std::pair<int, std::string> >
        suggestions;


    std::priority_queue<std::pair<int, std::string> > *Suggestions =
        &suggestions;

    for (auto &i : key) {
        letter_index = tolower(i) - 97;
        prev_pos = cur_pos;




        if (cur_pos->english[letter_index] == nullptr) {
            SuggestFreqAutocomplete(prev_pos, prefix, Suggestions);

            SelectionTop_3(Suggestions);
            std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - "
                      << std::endl;
            return;
        }

        prefix += char(tolower(i));
        cur_pos = cur_pos->english[letter_index];
    }

    if (cur_pos->endOfWord) {
        (cur_pos->frequency)++;
        std::cout << key << std::endl;
    }

    (void)prev_pos;



    SuggestFreqAutocomplete(cur_pos, prefix, Suggestions);

    SelectionTop_3(Suggestions);

    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - "
              << std::endl;
    return;
}
}
}


static void test() {
    auto root = new operations_on_datastructures::trie_operations::Tnode();
    std::vector<std::string> inputs = {
        "abcde", "sss",    "ssss",  "ssst", "sssu", "sssv",
        "sst",   "ssts",   "sstt",  "sstu", "tutu", "tutuv",
        "tutuu", "tutuvs", "tutus", "tvst", "tvsu", "vvvv"};

    for (auto &i : inputs) {
        root->Insert(i);
    }

    assert(root->SearchPresence("vvvv"));
    std::cout << root->SearchPresence("vvvv") << std::endl;

    root->Delete("vvvv");

    assert(!root->SearchPresence("vvvv"));
    std::cout << root->SearchPresence("vvvv") << std::endl;

    std::cout << root->SearchPresence("tutu") << std::endl;
    root->SearchSuggestions("tutu");
    std::cout << root->SearchPresence("tutu") << std::endl;

    root->SearchSuggestions("tutuv");
    std::cout << root->SearchPresence("tutuv") << std::endl;

    root->SearchSuggestions("tutuvs");

    root->SearchFreqSuggestions(
        "tu");

    root->SearchSuggestions(
        "");
}


int main(int argc, char const *argv[]) {
    test();
    return 0;
}
