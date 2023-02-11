#include "app/linal/include/vector.h"
#include <iostream>

int main(int argc, char **argv) {
  linal::vector<int, 10> a({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
  linal::vector<int, 10> b({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });

  std::cout << a << std::endl;

  std::cout << a - b << std::endl;
  std::cout << a + b << std::endl;
  a += b;
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  a += b;
  std::cout << a << std::endl;
  return 0;
}