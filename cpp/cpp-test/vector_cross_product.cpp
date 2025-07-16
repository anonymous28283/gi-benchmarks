







namespace math {

	namespace vector_cross {

		std::array<double, 3> cross(const std::array<double, 3> &A, const std::array<double, 3> &B) {
			std::array<double, 3> product;

			product[0] = (A[1] * B[2]) - (A[2] * B[1]);
			product[1] = -((A[0] * B[2]) - (A[2] * B[0]));
			product[2] = (A[0] * B[1]) - (A[1] * B[0]);
			return product;
		}


		double mag(const std::array<double, 3> &vec) {
			double magnitude = sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2]));
			return magnitude;
		}
	}
}


static void test() {

	std::array<double, 3> t_vec = math::vector_cross::cross({1, 2, 3}, {4, 5, 6});
	assert(t_vec[0] == -3 && t_vec[1] == 6 && t_vec[2] == -3);


	double t_mag = math::vector_cross::mag({6, 8, 0});
	assert(t_mag == 10);
}


int main() {


	test();

	std::array<double, 3> vec1;
	std::array<double, 3> vec2;


	std::cout << "\nPass the first Vector: ";
	std::cin >> vec1[0] >> vec1[1] >> vec1[2];


	std::cout << "\nPass the second Vector: ";
	std::cin >> vec2[0] >> vec2[1] >> vec2[2];


	std::array<double, 3> product = math::vector_cross::cross(vec1, vec2);
	std::cout << "\nThe cross product is: " << product[0] << " " << product[1] << " " << product[2] << std::endl;


	std::cout << "Magnitude: " << math::vector_cross::mag(product) << "\n" << std::endl;

	return 0;
}
