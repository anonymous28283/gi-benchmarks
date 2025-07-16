




namespace numerical_methods {

namespace false_position {

static float eq(float x) {
    return (x * x - x);
}


static float regula_falsi(float x1, float x2, float y1, float y2) {
    float diff = x1 - x2;
    if (diff < 0) {
        diff = (-1) * diff;
    }
    if (diff < 0.00001) {
        if (y1 < 0) {
            y1 = -y1;
        }
        if (y2 < 0) {
            y2 = -y2;
        }
        if (y1 < y2) {
            return x1;
        } else {
            return x2;
        }
    }
    float x3 = 0, y3 = 0;
    x3 = x1 - (x1 - x2) * (y1) / (y1 - y2);
    y3 = eq(x3);
    return regula_falsi(x2, x3, y2, y3);
}


void printRoot(float root, const int16_t &count) {
    if (count == 1) {
        std::cout << "Your 1st root is : " << root << std::endl;
    } else if (count == 2) {
        std::cout << "Your 2nd root is : " << root << std::endl;
    } else if (count == 3) {
        std::cout << "Your 3rd root is : " << root << std::endl;
    } else {
        std::cout << "Your " << count << "th root is : " << root << std::endl;
    }
}
}
}


int main() {
    float a = 0, b = 0, i = 0, root = 0;
    int16_t count = 0;
    float range =
        100000;
    float gap = 0.5;
    a = numerical_methods::false_position::eq((-1) * range);
    i = ((-1) * range + gap);


    while (i <= range) {
        b = numerical_methods::false_position::eq(i);
        if (b == 0) {
            count++;
            numerical_methods::false_position::printRoot(i, count);
        }
        if (a * b < 0) {
            root = numerical_methods::false_position::regula_falsi(i - gap, i,
                                                                   a, b);
            count++;
            numerical_methods::false_position::printRoot(root, count);
        }
        a = b;
        i += gap;
    }
    return 0;
}
