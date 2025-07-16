











namespace strings {

namespace boyer_moore {

struct pattern {
    std::string pat;

    std::vector<size_t>
        bad_char;


    std::vector<size_t>
        good_suffix;

};


void init_good_suffix(const std::string& str, std::vector<size_t>& arg) {
    arg.resize(str.size() + 1, 0);



    std::vector<size_t> border_pos(str.size() + 1, 0);

    size_t current_char = str.length();

    size_t border_index = str.length() + 1;

    border_pos[current_char] = border_index;

    while (current_char > 0) {
        while (border_index <= str.length() &&
               str[current_char - 1] != str[border_index - 1]) {
            if (arg[border_index] == 0) {
                arg[border_index] = border_index - current_char;
            }

            border_index = border_pos[border_index];
        }

        current_char--;
        border_index--;
        border_pos[current_char] = border_index;
    }

    size_t largest_border_index = border_pos[0];

    for (size_t i = 0; i < str.size(); i++) {
        if (arg[i] == 0) {
            arg[i] = largest_border_index;
        }


        if (i == largest_border_index) {
            largest_border_index = border_pos[largest_border_index];
        }
    }
}


void init_bad_char(const std::string& str, std::vector<size_t>& arg) {
    arg.resize(APLHABET_SIZE, str.length());

    for (size_t i = 0; i < str.length(); i++) {
        arg[str[i]] = str.length() - i - 1;
    }
}


void init_pattern(const std::string& str, pattern& arg) {
    arg.pat = str;
    init_bad_char(str, arg.bad_char);
    init_good_suffix(str, arg.good_suffix);
}

std::vector<size_t> search(const std::string& str, const pattern& arg) {
    size_t index_position = arg.pat.size() - 1;
    std::vector<size_t> index_storage;

    while (index_position < str.length()) {
        size_t index_string = index_position;
        int index_pattern = static_cast<int>(arg.pat.size()) - 1;

        while (index_pattern >= 0 &&
               str[index_string] == arg.pat[index_pattern]) {
            --index_pattern;
            --index_string;
        }

        if (index_pattern < 0) {
            index_storage.push_back(index_position - arg.pat.length() + 1);
            index_position += arg.good_suffix[0];
        } else {
            index_position += std::max(arg.bad_char[str[index_string]],
                                       arg.good_suffix[index_pattern + 1]);
        }
    }

    return index_storage;
}


bool is_prefix(const char* str, const char* pat, size_t len) {
    if (strlen(str) < len) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        if (str[i] != pat[i]) {
            return false;
        }
    }

    return true;
}
}
}

void and_test(const char* text) {
    strings::boyer_moore::pattern ands;
    strings::boyer_moore::init_pattern("and", ands);
    std::vector<size_t> indexes = strings::boyer_moore::search(text, ands);

    assert(indexes.size() == 2);
    assert(strings::boyer_moore::is_prefix(text + indexes[0], "and", 3));
    assert(strings::boyer_moore::is_prefix(text + indexes[1], "and", 3));
}


void pat_test(const char* text) {
    strings::boyer_moore::pattern pat;
    strings::boyer_moore::init_pattern("pat", pat);
    std::vector<size_t> indexes = strings::boyer_moore::search(text, pat);

    assert(indexes.size() == 6);

    for (const auto& currentIndex : indexes) {
        assert(strings::boyer_moore::is_prefix(text + currentIndex, "pat", 3));
    }
}

static void tests() {
    const char* text =
        "When pat Mr. and Mrs. pat Dursley woke up on the dull, gray  \
                            Tuesday our story starts, \
                there was nothing about pat the cloudy sky outside to pat suggest that\
                        strange and \
                    mysterious things would pat soon be happening all pat over the \
                        country.";

    and_test(text);
    pat_test(text);

    std::cout << "All tests have successfully passed!\n";
}


int main() {
    tests();
    return 0;
}
