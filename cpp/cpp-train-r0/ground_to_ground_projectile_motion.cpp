







namespace physics {

namespace ground_to_ground_projectile_motion {


double degrees_to_radians(double degrees){
    double radians = degrees * (M_PI / 180);
    return radians;
}


template <typename T>
T time_of_flight(T initial_velocity, T angle, double gravity = 9.81) {
    double Viy = initial_velocity * (std::sin(degrees_to_radians(angle)));
    return 2.0 * Viy / gravity;
}


template <typename T>
T horizontal_range(T initial_velocity, T angle, T time) {
    double Vix = initial_velocity * (std::cos(degrees_to_radians(angle)));
    return Vix * time;
}


template <typename T>
T max_height(T initial_velocity, T angle, double gravity = 9.81) {
    double Viy = initial_velocity * (std::sin(degrees_to_radians(angle)));
    return (std::pow(Viy, 2) / (2.0 * gravity));
}
}
}


static void test() {

    double initial_velocity = 5.0;
    double angle = 40.0;


    double expected_time_of_flight = 0.655;
    double flight_time_output =
        std::round(physics::ground_to_ground_projectile_motion::time_of_flight(initial_velocity, angle) * 1000.0) /
        1000.0;

    std::cout << "Projectile Flight Time (double)" << std::endl;
    std::cout << "Input Initial Velocity: " << initial_velocity << std::endl;
    std::cout << "Input Angle: " << angle << std::endl;
    std::cout << "Expected Output: " << expected_time_of_flight << std::endl;
    std::cout << "Output: " << flight_time_output << std::endl;
    assert(flight_time_output == expected_time_of_flight);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    double expected_horizontal_range = 2.51;
    double horizontal_range_output =
        std::round(physics::ground_to_ground_projectile_motion::horizontal_range(initial_velocity, angle,
                                             flight_time_output) *
                   100.0) /
        100.0;

    std::cout << "Projectile Horizontal Range (double)" << std::endl;
    std::cout << "Input Initial Velocity: " << initial_velocity << std::endl;
    std::cout << "Input Angle: " << angle << std::endl;
    std::cout << "Input Time Of Flight: " << flight_time_output << std::endl;
    std::cout << "Expected Output: " << expected_horizontal_range << std::endl;
    std::cout << "Output: " << horizontal_range_output << std::endl;
    assert(horizontal_range_output == expected_horizontal_range);
    std::cout << "TEST PASSED" << std::endl << std::endl;


    double expected_max_height = 0.526;
    double max_height_output =
        std::round(physics::ground_to_ground_projectile_motion::max_height(initial_velocity, angle) * 1000.0) /
        1000.0;

    std::cout << "Projectile Max Height (double)" << std::endl;
    std::cout << "Input Initial Velocity: " << initial_velocity << std::endl;
    std::cout << "Input Angle: " << angle << std::endl;
    std::cout << "Expected Output: " << expected_max_height << std::endl;
    std::cout << "Output: " << max_height_output << std::endl;
    assert(max_height_output == expected_max_height);
    std::cout << "TEST PASSED" << std::endl << std::endl;
}


int main() {
    test();
    return 0;
}
