#pragma once
#include "app/linal/include/matrix.h"
#include "app/linal/include/vector.h"
#include "diagonal-predominance.h"
#include <cmath>
#include <iostream>

namespace sle {
namespace method {
namespace iteration {

template <typename T, std::size_t N>
static linal::matrix<T, N, N>
build_alpha(const diagonal_predominant_matrix<T, N> &a) {
  linal::matrix<T, N, N> alpha;
  for (std::size_t i = 0; i < N; i++) {
    for (std::size_t j = 0; j < N; j++) {
      alpha[i][j] = -a[i][j] / a[i][i];
    }
  }
  for (std::size_t i = 0; i < N; i++) {
    alpha[i][i] = 0;
  }
  return alpha;
}

template <typename T, std::size_t N>
static linal::vector<T, N>
build_beta(const diagonal_predominant_matrix<T, N> &a,
           const linal::vector<T, N> &b) {
  linal::vector<T, N> beta;
  for (std::size_t i = 0; i < N; i++) {
    beta[i] = b[i] / a[i][i];
  }
  return beta;
}

template <typename T, std::size_t N>
T max_by_abs_component(const linal::vector<T, N> &x) noexcept {
  T max = std::abs(x[0]);
  for (std::size_t i = 1; i < N; i++) {
    max = std::max(max, std::abs(x[i]));
  }
  return max;
}

template <typename T, std::size_t N>
linal::vector<T, N> solve(const diagonal_predominant_matrix<T, N> &a,
                          const linal::vector<T, N> &b) {
  // TODO: support abstract fields
  const T eps = 0.01;
  const auto alpha = build_alpha(a);
  const auto beta = build_beta(a, b);

  linal::vector<T, N> x, prev;
  do {
    prev = x;
    alpha.apply_inplace(x);
    x += beta;
  } while (max_by_abs_component<T, N>(prev - x) > eps);

  return x;
}

} // namespace iteration
} // namespace method
} // namespace sle