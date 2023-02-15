#include "app/linal/include/matrix.h"
#include "app/linal/include/vector.h"
#include "app/sle/include/method/iteration/solution.h"
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  if (argc > 1) {
    std::string filename(argv[1]);
    freopen(filename.c_str(), "r", stdin);
  }

  const std::size_t N = 3;
  typedef float F;

  std::size_t size;
  std::cin >> size;

  linal::matrix<F, N, N> a;
  linal::vector<F, N> b;

  for (std::size_t i = 0; i < size; i++) {
    for (std::size_t j = 0; j < size; j++) {
      std::cin >> a[i][j];
    }
    std::cin >> b[i];
  }

  for (std::size_t i = size; i < N; i++) {
    for (std::size_t j = size; j < N; j++) {
      a[i][j] = 0;
    }
  }

  for (std::size_t i = size; i < N; i++) {
    a[i][i] = 1;
    b[i] = 1;
  }

  try {
    auto A = sle::method::iteration::diagonal_predominant_matrix<F, N>::make(a);
    std::cout << A << std::endl;
    auto result = sle::method::iteration::solve(A, b);
    std::cout << "result.value = " << result.value << std::endl;
    std::cout << "result.error = " << result.error << std::endl;
    std::cout << "result.steps_count = " << result.steps_count << std::endl;
  } catch (std::logic_error &e) {
    std::cerr << "error: " << e.what() << std::endl;
  }
  return 0;
}