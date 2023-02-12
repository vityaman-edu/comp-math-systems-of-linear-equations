#include "app/linal/include/matrix.h"
#include "app/linal/include/vector.h"
#include "app/sle/include/method/iteration/solution.h"
#include <iostream>

int main(int argc, char **argv) {
  const std::size_t N = 3;
  typedef double F;

  auto a = linal::matrix<F, N, N>(
      {{4, 0.24, -0.08}, {0.09, 3, -0.15}, {0.04, -0.08, 4}});
  auto b = linal::vector<F, N>({8, 9, 20});

  std::cout << a << std::endl;
  std::cout << b << std::endl;

  auto A = sle::method::iteration::diagonal_predominant_matrix<F, N>::make(a);
  std::cout << sle::method::iteration::solve(A, b) << std::endl;
  return 0;
}