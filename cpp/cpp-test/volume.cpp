







namespace math {

template <typename T>
T cube_volume(T length) {
    return std::pow(length, 3);
}


template <typename T>
T rect_prism_volume(T length, T width, T height) {
    return length * width * height;
}


template <typename T>
T cone_volume(T radius, T height, double PI = 3.14) {
    return std::pow(radius, 2) * PI * height / 3;
}


template <typename T>
T triangle_prism_volume(T base, T height, T depth) {
    return base * height * depth / 2;
}


template <typename T>
T pyramid_volume(T length, T width, T height) {
    return length * width * height / 3;
}


template <typename T>
T sphere_volume(T radius, double PI = 3.14) {
    return PI * std::pow(radius, 3) * 4 / 3;
}


template <typename T>
T cylinder_volume(T radius, T height, double PI = 3.14) {
    return PI * std::pow(radius, 2) * height;
}
}


static void test() {

    uint32_t int_length = 0;
    uint32_t int_width = 0;
    uint32_t int_base = 0;
    uint32_t int_height = 0;
    uint32_t int_depth = 0;

    double double_radius = NAN;
    double double_height = NAN;


    uint32_t int_expected = 0;
    uint32_t int_volume = 0;

    double double_expected = NAN;
    double double_volume = NAN;


    int_length = 5;
    int_expected = 125;
    int_volume = math::cube_volume(int_length);

    std::cout << "VOLUME OF A CUBE" << std::endl;
    std::cout << "Input Length: " << int_length << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_volume << std::endl;
    assert(int_volume == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    int_length = 4;
    int_width = 3;
    int_height = 5;
    int_expected = 60;
    int_volume = math::rect_prism_volume(int_length, int_width, int_height);

    std::cout << "VOLUME OF A RECTANGULAR PRISM" << std::endl;
    std::cout << "Input Length: " << int_length << std::endl;
    std::cout << "Input Width: " << int_width << std::endl;
    std::cout << "Input Height: " << int_height << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_volume << std::endl;
    assert(int_volume == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    double_radius = 5;
    double_height = 7;
    double_expected = 183.16666666666666;
    double_volume = math::cone_volume(double_radius, double_height);

    std::cout << "VOLUME OF A CONE" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Input Height: " << double_height << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_volume << std::endl;
    assert(double_volume == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    int_base = 3;
    int_height = 4;
    int_depth = 5;
    int_expected = 30;
    int_volume = math::triangle_prism_volume(int_base, int_height, int_depth);

    std::cout << "VOLUME OF A TRIANGULAR PRISM" << std::endl;
    std::cout << "Input Base: " << int_base << std::endl;
    std::cout << "Input Height: " << int_height << std::endl;
    std::cout << "Input Depth: " << int_depth << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_volume << std::endl;
    assert(int_volume == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    int_length = 10;
    int_width = 3;
    int_height = 5;
    int_expected = 50;
    int_volume = math::pyramid_volume(int_length, int_width, int_height);

    std::cout << "VOLUME OF A PYRAMID" << std::endl;
    std::cout << "Input Length: " << int_length << std::endl;
    std::cout << "Input Width: " << int_width << std::endl;
    std::cout << "Input Height: " << int_height << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_volume << std::endl;
    assert(int_volume == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    double_radius = 3;
    double_expected = 113.04;
    double_volume = math::sphere_volume(double_radius);

    std::cout << "VOLUME OF A SPHERE" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_volume << std::endl;
    assert(double_volume == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    double_radius = 5;
    double_height = 2;
    double_expected = 157;
    double_volume = math::cylinder_volume(double_radius, double_height);

    std::cout << "VOLUME OF A CYLINDER" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Input Height: " << double_height << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_volume << std::endl;
    assert(double_volume == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;
}


int main() {
    test();
    return 0;
}
