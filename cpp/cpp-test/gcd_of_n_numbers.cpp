






namespace math {

namespace gcd_of_n_numbers {

int gcd_two(int x, int y) {

  if (y == 0) {
    return x;
  }
  if (x == 0) {
    return y;
  }
  return gcd_two(y, x % y);
}


template <std::size_t n>
bool check_all_zeros(const std::array<int, n> &a) {

  return std::all_of(a.begin(), a.end(), [](int x) { return x == 0; });
}


template <std::size_t n>
int gcd(const std::array<int, n> &a) {

  if (check_all_zeros(a)) {
    return -1;
  }


  int result = std::abs(a[0]);
  for (std::size_t i = 1; i < n; ++i) {
    result = gcd_two(result, std::abs(a[i]));
    if (result == 1) {
      break;
    }
  }
  return result;
}
}
}


static void test() {
  std::array<int, 1> array_1 = {0};
  std::array<int, 1> array_2 = {1};
  std::array<int, 2> array_3 = {0, 2};
  std::array<int, 3> array_4 = {-60, 24, 18};
  std::array<int, 4> array_5 = {100, -100, -100, 200};
  std::array<int, 5> array_6 = {0, 0, 0, 0, 0};
  std::array<int, 7> array_7 = {10350, -24150, 0, 17250, 37950, -127650, 51750};
  std::array<int, 7> array_8 = {9500000, -12121200, 0, 4444, 0, 0, 123456789};

  assert(math::gcd_of_n_numbers::gcd(array_1) == -1);
  assert(math::gcd_of_n_numbers::gcd(array_2) == 1);
  assert(math::gcd_of_n_numbers::gcd(array_3) == 2);
  assert(math::gcd_of_n_numbers::gcd(array_4) == 6);
  assert(math::gcd_of_n_numbers::gcd(array_5) == 100);
  assert(math::gcd_of_n_numbers::gcd(array_6) == -1);
  assert(math::gcd_of_n_numbers::gcd(array_7) == 3450);
  assert(math::gcd_of_n_numbers::gcd(array_8) == 1);
}


int main() {
  test();
  return 0;
}
