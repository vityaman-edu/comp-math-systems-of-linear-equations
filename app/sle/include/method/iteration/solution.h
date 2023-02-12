#pragma once
#include "app/linal/include/matrix.h"
#include "app/linal/include/vector.h"
#include "diagonal-predominance.h"
#include <iostream>

namespace sle {
namespace method {
namespace iteration {

template <typename T, std::size_t N>
linal::vector<T, N> solve(const diagonal_predominant_matrix<T, N> &a,
                          const linal::vector<T, N> &b) {
  std::cout << "Hello, World" << std::endl;
  return linal::vector<T, N>::zero();
}

} // namespace iteration
} // namespace method
} // namespace sle