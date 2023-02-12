#include "app/linal/include/matrix.h"
#include "app/linal/include/vector.h"
#include <iostream>

int main(int argc, char **argv) {
  auto matrix = linal::matrix<int, 3, 3>::id();
  std::cout << matrix << std::endl;
  return 0;
}