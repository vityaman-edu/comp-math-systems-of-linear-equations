#include "math/linal/matrix.h"
#include "math/sle/method/gauss/solution.h"
#include "math/sle/method/iteration/solution.h"
#include "math/sle/method/iteration/valid-sle.h"
#include <fstream>
#include <functional>
#include <iostream>

template <typename T, std::size_t N>
void vector_print(
    const std::string& prefix,
    const math::linal::fixed_matrix<T, N, 1>& vec,
    std::size_t n
) {
  std::cout << prefix << " { ";
  for (std::size_t i = 0; i < n - 1; i++) {
    std::cout << vec(i, 0) << ", ";
  }
  if (1 < n) {
    std::cout << vec(n - 1, 0);
  }
  std::cout << " }" << std::endl;
}

int main(int argc, char** argv) {
  using namespace math::sle::method;

  if (argc > 1) {
    std::string filename(argv[1]);
    freopen(filename.c_str(), "r", stdin);
  }

  const std::size_t N = 20;
  typedef double F;
  const F DUMMY = 600;

  F eps;
  std::cin >> eps;

  std::size_t size;
  std::cin >> size;

  math::linal::fixed_matrix<F, N, N> a;
  math::linal::fixed_matrix<F, N, 1> b;

  for (std::size_t i = 0; i < size; i++) {
    for (std::size_t j = 0; j < size; j++) {
      std::cin >> a(i, j);
    }
    std::cin >> b(i, 0);
  }

  for (std::size_t i = size; i < N; i++) {
    a(i, i) = DUMMY;
    b(i, 0) = DUMMY;
  }

  std::cout << "Solving using gauss method..." << std::endl;
  auto peek = &math::sle::method::gauss::peek_max_by_abs<F>;
  auto result = gauss::solve<F, N>(a, b, peek);
  vector_print("result = ", result, size);
  std::cout << std::endl;

  try {
    std::cout << "Solving using iteration method..."
              << std::endl;
    using iteration::valid_sle;
    auto sle = valid_sle<F, N>::make(a, b);
    auto result = iteration::solve(sle, eps);
    vector_print("result.value = ", result.value, size);
    vector_print("result.error = ", result.error, size);
    std::cout << "result.steps_count = " << result.steps_count
              << std::endl;
  } catch (std::logic_error& e) {
    std::cerr << "error: " << e.what() << std::endl;
  }

  return 0;
}
