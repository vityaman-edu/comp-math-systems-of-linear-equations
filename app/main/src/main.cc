#include "app/linal/include/matrix.h"
#include "app/linal/include/vector.h"
#include "app/sle/include/method/iteration/solution.h"
#include <iostream>

int main(int argc, char **argv) {
  const std::size_t N = 5;
  typedef float F;
  auto a = linal::matrix<F, N, N>({
    {5, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 6, 0, 0},
    {0, 1, 0, 3, 0},
    {0, 1, 0, 0, 2}
  });
  auto b = linal::vector<F, N>(); 
  auto A = sle::method::iteration::diagonal_predominant_matrix<F, N>::make(a);
  A += a;
  std::cout << A << std::endl;
  std::cout << a << std::endl;
  std::cout << sle::method::iteration::solve(A, b) << std::endl;
  return 0;
}