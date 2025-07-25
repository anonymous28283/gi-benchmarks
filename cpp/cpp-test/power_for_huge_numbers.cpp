






int multiply(int x, int res[], int res_size) {

    int carry = 0;



    for (int i = 0; i < res_size; i++) {
        int prod = res[i] * x + carry;



        res[i] = prod % 10;


        carry = prod / 10;
    }



    while (carry) {
        res[res_size] = carry % 10;
        carry = carry / 10;
        res_size++;
    }
    return res_size;
}


void power(int x, int n) {

    if (n == 0) {
        std::cout << "1";
        return;
    }

    int res[MAX];
    int res_size = 0;
    int temp = x;


    while (temp != 0) {
        res[res_size++] = temp % 10;
        temp = temp / 10;
    }



    for (int i = 2; i <= n; i++) res_size = multiply(x, res, res_size);

    std::cout << x << "^" << n << " = ";
    for (int i = res_size - 1; i >= 0; i--) std::cout << res[i];
}


int main() {
    int exponent, base;
    std::cout << "Enter base ";
    std::cin >> base;
    std::cout << "Enter exponent ";
    std::cin >> exponent;
    power(base, exponent);
    return 0;
}
