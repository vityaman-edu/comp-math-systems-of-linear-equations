#pragma once
#include "app/linal/include/matrix.h"
#include "app/linal/include/vector.h"
#include "valid-sle.h"
#include <cmath>
#include <functional>
#include <iostream>

namespace sle {
namespace method {
namespace iteration {

template <typename T, std::size_t N>
static linal::matrix<T, N, N> build_alpha(const valid_sle<T, N> &sle) {
  linal::matrix<T, N, N> alpha;
  for (std::size_t i = 0; i < N; i++) {
    for (std::size_t j = 0; j < N; j++) {
      alpha[i][j] = -sle.left()[i][j] / sle.left()[i][i];
    }
  }
  for (std::size_t i = 0; i < N; i++) {
    alpha[i][i] = 0;
  }
  return alpha;
}

template <typename T, std::size_t N>
static linal::vector<T, N> build_beta(const valid_sle<T, N> &sle) {
  linal::vector<T, N> beta;
  for (std::size_t i = 0; i < N; i++) {
    beta[i] = sle.right()[i] / sle.left()[i][i];
  }
  return beta;
}

template <typename T, std::size_t N>
T max_component(const linal::vector<T, N> &x) noexcept {
  T max = x[0];
  for (std::size_t i = 1; i < N; i++) {
    max = std::max(max, x[i]);
  }
  return max;
}

template <typename T, std::size_t N> struct result {
  linal::vector<T, N> value;
  std::size_t steps_count;
  linal::vector<T, N> error;
};

template <typename T, std::size_t N>
result<T, N> solve(const valid_sle<T, N> &sle) {
  // TODO: support abstract fields
  const T EPS = 0.0001;
  const auto alpha = build_alpha(sle);
  const auto beta = build_beta(sle);

  std::size_t steps_count = 0;
  linal::vector<T, N> x, prev;
  do {
    prev = x;
    x = alpha * x;
    x += beta;

    steps_count += 1;
    auto error = linal::map<T, T, N>(prev - x, [](T v) { return std::abs(v); });

    if (max_component<T, N>(error) < EPS) {
      return {.value = x, .steps_count = steps_count, .error = error};
    }
  } while (true);
}

} // namespace iteration
} // namespace method
} // namespace sle