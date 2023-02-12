#include "app/linal/include/matrix.h"
#include "app/linal/include/vector.h"
#include <iostream>

int main(int argc, char **argv) {
  linal::matrix<int, 3, 3> matrix({
    {1, 2, 3},
    {3, 4, 5},
    {6, 7, 8}
  });
  std::cout << matrix << std::endl;
  return 0;
}