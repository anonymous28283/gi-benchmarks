







template <typename T = double, char iterations = 2>
inline T Fast_InvSqrt(T x) {
    using Tint = typename std::conditional<sizeof(T) == 8, std::int64_t,
                                           std::int32_t>::type;
    T y = x;
    T x2 = y * 0.5;

    Tint i =
        *reinterpret_cast<Tint *>(&y);

    i = (sizeof(T) == 8 ? 0x5fe6eb50c7b537a9 : 0x5f3759df) -
        (i >> 1);

    y = *reinterpret_cast<T *>(&i);

    y = y * (1.5 - (x2 * y * y));
    if (iterations == 2) {
        y = y * (1.5 - (x2 * y * y));
    }
    return y;
}


template <typename T = double>
T Standard_InvSqrt(T number) {
    T squareRoot = sqrt(number);
    return 1.0f / squareRoot;
}


static void test() {
    const float epsilon = 1e-3f;


    assert(std::fabs(Standard_InvSqrt<float>(100.0f) - 0.0998449f) < epsilon);
    assert(std::fabs(Standard_InvSqrt<double>(36.0f) - 0.166667f) < epsilon);
    assert(std::fabs(Standard_InvSqrt(12.0f) - 0.288423f) < epsilon);
    assert(std::fabs(Standard_InvSqrt<double>(5.0f) - 0.447141f) < epsilon);

    assert(std::fabs(Fast_InvSqrt<float, 1>(100.0f) - 0.0998449f) < epsilon);
    assert(std::fabs(Fast_InvSqrt<double, 1>(36.0f) - 0.166667f) < epsilon);
    assert(std::fabs(Fast_InvSqrt(12.0f) - 0.288423) < epsilon);
    assert(std::fabs(Fast_InvSqrt<double>(5.0f) - 0.447141) < epsilon);
}


int main() {
    test();
    std::cout << "The Fast inverse square root of 36 is: "
              << Fast_InvSqrt<float, 1>(36.0f) << std::endl;
    std::cout << "The Fast inverse square root of 36 is: "
              << Fast_InvSqrt<double, 2>(36.0f) << " (2 iterations)"
              << std::endl;
    std::cout << "The Fast inverse square root of 100 is: "
              << Fast_InvSqrt(100.0f)
              << " (With default template type and iterations: double, 2)"
              << std::endl;
    std::cout << "The Standard inverse square root of 36 is: "
              << Standard_InvSqrt<float>(36.0f) << std::endl;
    std::cout << "The Standard inverse square root of 100 is: "
              << Standard_InvSqrt(100.0f)
              << " (With default template type: double)" << std::endl;
}
