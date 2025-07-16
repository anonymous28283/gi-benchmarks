








namespace math {

template <typename T>
T square_area(T length) {
    return length * length;
}


template <typename T>
T rect_area(T length, T width) {
    return length * width;
}


template <typename T>
T triangle_area(T base, T height) {
    return base * height / 2;
}


template <typename T>
T circle_area(T radius) {
    return M_PI * pow(radius, 2);
}


template <typename T>
T parallelogram_area(T base, T height) {
    return base * height;
}


template <typename T>
T cube_surface_area(T length) {
    return 6 * length * length;
}


template <typename T>
T sphere_surface_area(T radius) {
    return 4 * M_PI * pow(radius, 2);
}


template <typename T>
T cylinder_surface_area(T radius, T height) {
    return 2 * M_PI * radius * height + 2 * M_PI * pow(radius, 2);
}


template <typename T>
T hemi_sphere_surface_area(T radius) {
    return 3 * M_PI * pow(radius, 2);
}
}


static void test() {

    uint16_t int_length = 0;
    uint16_t int_width = 0;
    uint16_t int_base = 0;
    uint16_t int_height = 0;
    uint16_t int_expected = 0;
    uint16_t int_area = 0;

    float float_length = NAN;
    float float_expected = NAN;
    float float_area = NAN;

    double double_length = NAN;
    double double_width = NAN;
    double double_radius = NAN;
    double double_height = NAN;
    double double_expected = NAN;
    double double_area = NAN;


    int_length = 5;
    int_expected = 25;
    int_area = math::square_area(int_length);

    std::cout << "AREA OF A SQUARE (int)" << std::endl;
    std::cout << "Input Length: " << int_length << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_area << std::endl;
    assert(int_area == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    float_length = 2.5;
    float_expected = 6.25;
    float_area = math::square_area(float_length);

    std::cout << "AREA OF A SQUARE (float)" << std::endl;
    std::cout << "Input Length: " << float_length << std::endl;
    std::cout << "Expected Output: " << float_expected << std::endl;
    std::cout << "Output: " << float_area << std::endl;
    assert(float_area == float_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    int_length = 4;
    int_width = 7;
    int_expected = 28;
    int_area = math::rect_area(int_length, int_width);

    std::cout << "AREA OF A RECTANGLE (int)" << std::endl;
    std::cout << "Input Length: " << int_length << std::endl;
    std::cout << "Input Width: " << int_width << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_area << std::endl;
    assert(int_area == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    double_length = 2.5;
    double_width = 5.7;
    double_expected = 14.25;
    double_area = math::rect_area(double_length, double_width);

    std::cout << "AREA OF A RECTANGLE (double)" << std::endl;
    std::cout << "Input Length: " << double_length << std::endl;
    std::cout << "Input Width: " << double_width << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_area << std::endl;
    assert(double_area == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    int_base = 10;
    int_height = 3;
    int_expected = 15;
    int_area = math::triangle_area(int_base, int_height);

    std::cout << "AREA OF A TRIANGLE" << std::endl;
    std::cout << "Input Base: " << int_base << std::endl;
    std::cout << "Input Height: " << int_height << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_area << std::endl;
    assert(int_area == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    double_radius = 6;
    double_expected =
        113.09733552923255;

    double_area = math::circle_area(double_radius);

    std::cout << "AREA OF A CIRCLE" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_area << std::endl;
    assert(double_area == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    int_base = 6;
    int_height = 7;
    int_expected = 42;
    int_area = math::parallelogram_area(int_base, int_height);

    std::cout << "AREA OF A PARALLELOGRAM" << std::endl;
    std::cout << "Input Base: " << int_base << std::endl;
    std::cout << "Input Height: " << int_height << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_area << std::endl;
    assert(int_area == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    double_length = 5.5;
    double_expected = 181.5;
    double_area = math::cube_surface_area(double_length);

    std::cout << "SURFACE AREA OF A CUBE" << std::endl;
    std::cout << "Input Length: " << double_length << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_area << std::endl;
    assert(double_area == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    double_radius = 10.0;
    double_expected = 1256.6370614359172;

    double_area = math::sphere_surface_area(double_radius);

    std::cout << "SURFACE AREA OF A SPHERE" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_area << std::endl;
    assert(double_area == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    double_radius = 4.0;
    double_height = 7.0;
    double_expected = 276.46015351590177;
    double_area = math::cylinder_surface_area(double_radius, double_height);

    std::cout << "SURFACE AREA OF A CYLINDER" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Input Height: " << double_height << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_area << std::endl;
    assert(double_area == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    double_radius = 10.0;
    double_expected = 942.4777960769379;
    double_area = math::hemi_sphere_surface_area(double_radius);

    std::cout << "SURFACE AREA OF A HEMI-SPHERE" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_area << std::endl;
    assert(double_area == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;
}


int main() {
    test();
    return 0;
}
