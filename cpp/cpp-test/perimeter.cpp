







namespace math {

template <typename T>
T square_perimeter(T length) {
    return 4 * length;
}


template <typename T>
T rect_perimeter(T length, T width) {
    return 2 * (length + width);
}


template <typename T>
T triangle_perimeter(T base, T height, T hypotenuse) {
    return base + height + hypotenuse;
}


template <typename T>
T circle_perimeter(T radius) {
    return 2 * M_PI * radius;
}


template <typename T>
T parallelogram_perimeter(T base, T height) {
    return 2 * (base + height);
}


template <typename T>
T cube_surface_perimeter(T length) {
    return 12 * length;
}


template <typename T>
T n_polygon_surface_perimeter(T sides, T length) {
    return sides * length;
}


template <typename T>
T cylinder_surface_perimeter(T radius, T height) {
    return (2 * radius) + (2 * height);
}
}


static void test() {

    uint16_t int_length = 0;
    uint16_t int_width = 0;
    uint16_t int_base = 0;
    uint16_t int_height = 0;
    uint16_t int_hypotenuse = 0;
    uint16_t int_sides = 0;
    uint16_t int_expected = 0;
    uint16_t int_perimeter = 0;

    float float_length = NAN;
    float float_expected = NAN;
    float float_perimeter = NAN;

    double double_length = NAN;
    double double_width = NAN;
    double double_radius = NAN;
    double double_height = NAN;
    double double_expected = NAN;
    double double_perimeter = NAN;


    int_length = 5;
    int_expected = 20;
    int_perimeter = math::square_perimeter(int_length);

    std::cout << "perimeter OF A SQUARE (int)" << std::endl;
    std::cout << "Input Length: " << int_length << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_perimeter << std::endl;
    assert(int_perimeter == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    float_length = 2.5;
    float_expected = 10;
    float_perimeter = math::square_perimeter(float_length);

    std::cout << "perimeter OF A SQUARE (float)" << std::endl;
    std::cout << "Input Length: " << float_length << std::endl;
    std::cout << "Expected Output: " << float_expected << std::endl;
    std::cout << "Output: " << float_perimeter << std::endl;
    assert(float_perimeter == float_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    int_length = 4;
    int_width = 7;
    int_expected = 22;
    int_perimeter = math::rect_perimeter(int_length, int_width);

    std::cout << "perimeter OF A RECTANGLE (int)" << std::endl;
    std::cout << "Input Length: " << int_length << std::endl;
    std::cout << "Input Width: " << int_width << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_perimeter << std::endl;
    assert(int_perimeter == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    double_length = 2.5;
    double_width = 5.7;
    double_expected = 16.4;
    double_perimeter = math::rect_perimeter(double_length, double_width);

    std::cout << "perimeter OF A RECTANGLE (double)" << std::endl;
    std::cout << "Input Length: " << double_length << std::endl;
    std::cout << "Input Width: " << double_width << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_perimeter << std::endl;
    assert(double_perimeter == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    int_base = 10;
    int_height = 3;
    int_hypotenuse = 5;
    int_expected = 18;
    int_perimeter =
        math::triangle_perimeter(int_base, int_height, int_hypotenuse);

    std::cout << "perimeter OF A TRIANGLE" << std::endl;
    std::cout << "Input Base: " << int_base << std::endl;
    std::cout << "Input Height: " << int_height << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_perimeter << std::endl;
    assert(int_perimeter == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    double_radius = 6;
    double_expected =
        37.69911184307752;

    double_perimeter = math::circle_perimeter(double_radius);

    std::cout << "perimeter OF A CIRCLE" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_perimeter << std::endl;
    assert(double_perimeter == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    int_base = 6;
    int_height = 7;
    int_expected = 26;
    int_perimeter = math::parallelogram_perimeter(int_base, int_height);

    std::cout << "perimeter OF A PARALLELOGRAM" << std::endl;
    std::cout << "Input Base: " << int_base << std::endl;
    std::cout << "Input Height: " << int_height << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_perimeter << std::endl;
    assert(int_perimeter == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    double_length = 5.5;
    double_expected = 66.0;
    double_perimeter = math::cube_surface_perimeter(double_length);

    std::cout << "SURFACE perimeter OF A CUBE" << std::endl;
    std::cout << "Input Length: " << double_length << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_perimeter << std::endl;
    assert(double_perimeter == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    int_sides = 7;
    int_length = 10;
    int_expected = 70;
    int_perimeter = math::n_polygon_surface_perimeter(int_sides, int_length);

    std::cout << "SURFACE perimeter OF A N-POLYGON" << std::endl;
    std::cout << "Input Sides: " << int_sides << std::endl;
    std::cout << "Input Length: " << int_length << std::endl;
    std::cout << "Expected Output: " << int_expected << std::endl;
    std::cout << "Output: " << int_perimeter << std::endl;
    assert(int_perimeter == int_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    double_radius = 4.0;
    double_height = 7.0;
    double_expected = 22.0;
    double_perimeter =
        math::cylinder_surface_perimeter(double_radius, double_height);

    std::cout << "SURFACE perimeter OF A CYLINDER" << std::endl;
    std::cout << "Input Radius: " << double_radius << std::endl;
    std::cout << "Input Height: " << double_height << std::endl;
    std::cout << "Expected Output: " << double_expected << std::endl;
    std::cout << "Output: " << double_perimeter << std::endl;
    assert(double_perimeter == double_expected);
    std::cout << "TEST PASSED" << std::endl << std::endl;
}


int main() {
    test();
    return 0;
}
