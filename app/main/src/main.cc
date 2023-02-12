#include "app/linal/include/matrix.h"
#include "app/linal/include/vector.h"
#include "app/sle/include/method/iteration/solution.h"
#include <iostream>

int main(int argc, char **argv) {
  auto a = linal::matrix<float, 3, 3>::id();
  auto b = linal::vector<float, 3>(); 
  auto A = sle::method::iteration::diagonal_predominant_matrix<float, 3>::make(a);
  A += a;
  std::cout << A << std::endl;
  std::cout << a << std::endl;
  std::cout << sle::method::iteration::solve(A, b) << std::endl;
  return 0;
}