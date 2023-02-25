#include "math/linal/matrix.h"
#include "math/sle/method/iteration/solution.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <type_traits>

template <typename T, std::size_t N>
void vector_print(
    const std::string& prefix,
    const math::linal::matrix<T, N, 1>& vec,
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
  math::linal::matrix<F, N, N> a =
      math::linal::matrix<F, N, N>::zero();
  math::linal::matrix<F, N, 1> b =
      math::linal::matrix<F, N, 1>::zero();

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

  try {
    auto sle =
        math::sle::method::iteration::valid_sle<F, N>::make(
            a, b
        );

    auto result = math::sle::method::iteration::solve(sle, eps);
    vector_print("result.value = ", result.value, size);
    vector_print("result.error = ", result.error, size);
    std::cout << "result.steps_count = " << result.steps_count
              << std::endl;
  } catch (std::logic_error& e) {
    std::cerr << "error: " << e.what() << std::endl;
  }

  return 0;
}
