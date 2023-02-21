#include "app/linal/include/matrix.h"
#include "app/linal/include/vector.h"
#include "app/sle/include/method/iteration/solution.h"
#include <fstream>
#include <iostream>

template <typename T, std::size_t N>
void vector_print(
  const std::string& prefix,
  const linal::vector<T, N>& vec,
  std::size_t n
) {
  std::cout << prefix << " { ";
  for (std::size_t i = 0; i < n - 1; i++) {
    std::cout << vec[i] << ", ";
  }
  if (1 < n) {
    std::cout << vec[n - 1];
  }
  std::cout << " }"  << std::endl;
}

int main(int argc, char **argv) {
  if (argc > 1) {
    std::string filename(argv[1]);
    freopen(filename.c_str(), "r", stdin);
  }

  const std::size_t N = 20;
  typedef float F;
  const F DUMMY = 600;

  F eps;
  std::cin >> eps;

  std::size_t size;
  std::cin >> size;

  // TODO: walkaround UB
  const F a_init[N][N] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  linal::matrix<F, N, N> a(a_init);
  const F b_init[N] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  linal::vector<F, N> b(b_init);

  for (std::size_t i = 0; i < size; i++) {
    for (std::size_t j = 0; j < size; j++) {
      std::cin >> a[i][j];
    }
    std::cin >> b[i];
  }

  for (std::size_t i = size; i < N; i++) {
    a[i][i] = DUMMY;
    b[i] = DUMMY;
  }

  try {
    auto sle = sle::method::iteration::valid_sle<F, N>::make(a, b);
    auto result = sle::method::iteration::solve(sle, eps);
    vector_print("result.value = ", result.value, size);
    vector_print("result.error = ", result.error, size);
    std::cout << "result.steps_count = " << result.steps_count << std::endl;
  } catch (std::logic_error &e) {
    std::cerr << "error: " << e.what() << std::endl;
  }
  return 0;
}
