









namespace sorting {

namespace bubble_sort {

template <typename T> 
std::vector<T> bubble_sort(std::vector<T>& array) {


  bool swap_check = true;
  int size = array.size();
  for (int i = 0; (i < size) && (swap_check); i++) {
    swap_check = false;
    for (int j = 0; j < size - 1 - i; j++) {
      if (array[j] > array[j + 1]) {
        swap_check = true;
        std::swap(array[j], array[j + 1]);
      }
    }
  }

  return array;
}
}
}


static void test() {
  std::vector<int> vec_1 = {3, 1, -9, 0};
  std::vector<int> sorted_1 = sorting::bubble_sort::bubble_sort(vec_1);

  std::vector<int> vec_2 = {3};
  std::vector<int> sorted_2 = sorting::bubble_sort::bubble_sort(vec_2);

  std::vector<int> vec_3 = {10, 10, 10, 10, 10};
  std::vector<int> sorted_3 = sorting::bubble_sort::bubble_sort(vec_3);

  std::vector<float> vec_4 = {1234, -273.1, 23, 150, 1234, 1555.55, -2000};
  std::vector<float> sorted_4 = sorting::bubble_sort::bubble_sort(vec_4);

  std::vector<char> vec_5 = {'z', 'Z', 'a', 'B', ' ', 'c', 'a'};
  std::vector<char> sorted_5 = sorting::bubble_sort::bubble_sort(vec_5);

  std::vector<std::string> vec_6 = {"Hello", "hello", "Helo", "Hi", "hehe"};
  std::vector<std::string> sorted_6 = sorting::bubble_sort::bubble_sort(vec_6);

  std::vector<std::pair<int, char>> vec_7 = {{10, 'c'}, {2, 'z'}, {10, 'a'}, {0, 'b'}, {-1, 'z'}};
  std::vector<std::pair<int, char>> sorted_7 = sorting::bubble_sort::bubble_sort(vec_7);

  assert(std::is_sorted(sorted_1.begin(), sorted_1.end()));
  assert(std::is_sorted(sorted_2.begin(), sorted_2.end()));
  assert(std::is_sorted(sorted_3.begin(), sorted_3.end()));
  assert(std::is_sorted(sorted_4.begin(), sorted_4.end()));
  assert(std::is_sorted(sorted_5.begin(), sorted_5.end()));
  assert(std::is_sorted(sorted_6.begin(), sorted_6.end()));
  assert(std::is_sorted(sorted_7.begin(), sorted_7.end()));
}


int main() {
  test();
  return 0;
}
