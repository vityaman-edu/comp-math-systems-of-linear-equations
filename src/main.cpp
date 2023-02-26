#include "math/linal/matrix.h"
#include "math/sle/method/gauss/solution.h"
#include "math/sle/method/iteration/solution.h"
#include "math/sle/method/iteration/valid-sle.h"
#include <fstream>
#include <functional>
#include <ios>
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

const std::size_t N = 5;
typedef double F;
const F DUMMY = 1;

template <typename T, std::size_t N>
void exec_gauss(
    const math::linal::fixed_matrix<T, N, N>& a,
    const math::linal::fixed_matrix<T, N, 1>& b,
    const std::size_t size
) {
  using namespace math::sle::method;
  auto peek = &math::sle::method::gauss::peek_max_by_abs<F>;
  auto result = gauss::solve<F, N>(a, b, peek);
  vector_print("result.value = ", result.value, size);
  std::cout << "|result.det| = " << result.det << std::endl;
  std::cout << "result.matrix = " << std::endl;
  for (std::size_t i = 0; i < size; i++) {
    for (std::size_t j = 0; j < size; j++) {
      std::cout << result.matrix(i, j) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

template <typename T, std::size_t N>
void exec_iteration(
    const math::linal::fixed_matrix<T, N, N>& a,
    const math::linal::fixed_matrix<T, N, 1>& b,
    const F eps,
    const std::size_t size
) {
  using namespace math::sle::method;
  using iteration::valid_sle;
  auto sle = valid_sle<F, N>::make(a, b);
  auto result = iteration::solve(sle, eps);
  vector_print("result.value = ", result.value, size);
  vector_print("result.error = ", result.error, size);
  std::cout << "result.steps_count = " << result.steps_count
            << std::endl;
}

int main(int argc, char** argv) {

  if (argc > 1) {
    std::string filename(argv[1]);
    freopen(filename.c_str(), "r", stdin);
  }

  std::cout << std::setprecision(3) << std::fixed;

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
  exec_gauss(a, b, size);

  std::cout << "Solving using iteration method..." << std::endl;
  try {
    exec_iteration(a, b, eps, size);
  } catch (std::logic_error& e) {
    std::cerr << "error: " << e.what() << std::endl;
  }

  return 0;
}
