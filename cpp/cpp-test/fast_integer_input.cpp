



void fastinput(int *number) {

    bool negative = false;
    int c;
    *number = 0;


    c = std::getchar();
    if (c == '-') {

        negative = true;


        c = std::getchar();
    }



    for (; (c > 47 && c < 58); c = std::getchar())
        *number = *number * 10 + c - 48;



    if (negative)
        *(number) *= -1;
}


int main() {
    int number;
    fastinput(&number);
    std::cout << number << std::endl;
    return 0;
}
