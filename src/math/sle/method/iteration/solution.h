#pragma once
#include "math/linal/matrix.h"
#include "valid-sle.h"
#include <cmath>
#include <functional>
#include <iostream>

namespace math {
namespace sle {
namespace method {
namespace iteration {

template <typename T, std::size_t N>
static linal::fixed_matrix<T, N, N>
build_alpha(const valid_sle<T, N>& sle) {
  linal::fixed_matrix<T, N, N> alpha;
  for (std::size_t i = 0; i < N; i++) {
    for (std::size_t j = 0; j < N; j++) {
      alpha(i, j) = -sle.left()(i, j) / sle.left()(i, i);
    }
  }
  for (std::size_t i = 0; i < N; i++) {
    alpha(i, i) = 0;
  }
  return alpha;
}

template <typename T, std::size_t N>
static linal::fixed_matrix<T, N, 1>
build_beta(const valid_sle<T, N>& sle) {
  linal::fixed_matrix<T, N, 1> beta;
  for (std::size_t i = 0; i < N; i++) {
    beta(i, 0) = sle.right()(i, 0) / sle.left()(i, i);
  }
  return beta;
}

template <typename T, std::size_t N>
linal::fixed_matrix<T, N, 1> abs(const linal::fixed_matrix<T, N, 1>& x
) noexcept {
  linal::fixed_matrix<T, N, 1> result;
  for (std::size_t i = 0; i < N; i++) {
    result(i, 0) = std::fabs(x(i, 0));
  }
  return result;
}

template <typename T, std::size_t N>
T max_component(const linal::fixed_matrix<T, N, 1>& x) noexcept {
  T max = x(0, 0);
  for (std::size_t i = 1; i < N; i++) {
    max = std::max(max, x(i, 0));
  }
  return max;
}

template <typename T, std::size_t N> struct result {
  linal::fixed_matrix<T, N, 1> value;
  std::size_t steps_count;
  linal::fixed_matrix<T, N, 1> error;
};

template <typename T, std::size_t N>
result<T, N> solve(const valid_sle<T, N>& sle, const T eps) {
  const auto alpha = build_alpha(sle);
  const auto beta = build_beta(sle);

  std::size_t steps_count = 0;
  linal::fixed_matrix<T, N, 1> x = beta;
  linal::fixed_matrix<T, N, 1> prev = beta;
  do {
    prev = x;
    x = alpha * x;
    x = x + beta;

    steps_count += 1;
    auto error = abs(prev - x);
    if (max_component<T, N>(error) < eps) {
      return {
          .value = x,
          .steps_count = steps_count,
          .error = error};
    }
  } while (true);
}

} // namespace iteration
} // namespace method
} // namespace sle
} // namespace math