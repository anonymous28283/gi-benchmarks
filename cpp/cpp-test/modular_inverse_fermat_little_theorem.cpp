






namespace math {

namespace modular_inverse_fermat {

std::int64_t binExpo(std::int64_t a, std::int64_t b, std::int64_t m) {
  a %= m;
  std::int64_t res = 1;
  while (b > 0) {
    if (b % 2 != 0) {
      res = res * a % m;
    }
    a = a * a % m;

    b >>= 1;
  }
  return res;
}

bool isPrime(std::int64_t m) {
  if (m <= 1) {
    return false;
  } 
  for (std::int64_t i = 2; i * i <= m; i++) {
    if (m % i == 0) {
      return false;
    }
  }
  return true;
}

std::int64_t modular_inverse(std::int64_t a, std::int64_t m) {
  while (a < 0) {
    a += m;
  }


  if (!isPrime(m) || a == 0) {
    return -1;
  }

  return binExpo(a, m - 2, m);
}
}
}


static void test() {
  assert(math::modular_inverse_fermat::modular_inverse(0, 97) == -1);
  assert(math::modular_inverse_fermat::modular_inverse(15, -2) == -1);
  assert(math::modular_inverse_fermat::modular_inverse(3, 10) == -1);
  assert(math::modular_inverse_fermat::modular_inverse(3, 7) == 5);
  assert(math::modular_inverse_fermat::modular_inverse(1, 101) == 1);
  assert(math::modular_inverse_fermat::modular_inverse(-1337, 285179) == 165519);
  assert(math::modular_inverse_fermat::modular_inverse(123456789, 998244353) == 25170271);
  assert(math::modular_inverse_fermat::modular_inverse(-9876543210, 1000000007) == 784794281);
}


int main() {
  test();
  return 0;
}
