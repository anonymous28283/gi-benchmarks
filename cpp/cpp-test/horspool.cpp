






namespace strings {

namespace horspool {

std::unordered_map<char, int> findShiftTable(const std::string &prototype) {
    std::unordered_map<char, int>
        shiftTable;

    for (int i = 0; i < prototype.size();
         i++) {
        if (shiftTable.find(prototype[i]) ==
            shiftTable.end()) {
            if (i != prototype.size() - 1) {
                shiftTable.insert(std::make_pair(
                    prototype[i], prototype.size() - i -
                                      1));
            } else {
                shiftTable.insert(std::make_pair(
                    prototype[i],
                    prototype.size()));
            }
        } else {
            if (i != prototype.size() - 1) {
                shiftTable[prototype[i]] = prototype.size() - i - 1;
            }
        }
    }
    return shiftTable;
}


bool horspool(const std::string &text, const std::string &prototype) {
    std::unordered_map<char, int> shiftTable = findShiftTable(
        prototype);

    int i = static_cast<int>(
        prototype.size() -
        1);
    while (i < text.size()) {
        int j = i, k = 0;
        bool flag = true;

        for (int z = static_cast<int>(prototype.size() - 1); z >= 0 && flag;
             z--) {
            if (text[j] == prototype[z]) {
                k++;
                j--;
            } else {
                flag = false;
            }
        }

        if (k ==
            prototype.size()) {
            return true;
        } else {
            if (shiftTable.find(text[i]) != shiftTable.end()) {
                i += shiftTable[text[i]];
            } else {
                i += prototype.size();
            }
        }
    }
    return false;
}
}
}


static void test(){
    assert(strings::horspool::horspool("Hello World","World") == true);
    assert(strings::horspool::horspool("Hello World"," World") == true);
    assert(strings::horspool::horspool("Hello World","ello") == true);
    assert(strings::horspool::horspool("Hello World","rld") == true);
    assert(strings::horspool::horspool("Hello","Helo") == false);
    assert(strings::horspool::horspool("c++_algorithms","c++_algorithms") == true);
    assert(strings::horspool::horspool("c++_algorithms","c++_") == true);
    assert(strings::horspool::horspool("Hello","Hello World") == false);
    assert(strings::horspool::horspool("c++_algorithms","") == false);
    assert(strings::horspool::horspool("c++","c") == true);
    assert(strings::horspool::horspool("3458934793","4793") == true);
    assert(strings::horspool::horspool("3458934793","123") == false);
}


int main(){
    test();
    return 0;
}
