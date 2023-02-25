#pragma once
#include "math/linal/matrix.h"
#include <cstddef>

namespace math {
namespace sle {
namespace method {
namespace gauss {

template <typename T> struct max_by_abs_result {
  std::size_t row;
  std::size_t col;
};

template <typename T, std::size_t N>
max_by_abs_result<T>
find_max_by_abs(const linal::matrix<T, N, N>& a) {
  std::size_t row = 0;
  std::size_t col = 0;
  for (std::size_t i = 0; i < N; i++) {
    for (std::size_t j = 0; j < N; j++) {
      if (std::abs(a(row, col)) < std::abs(a(i, j))) {
        row = i;
        col = j;
      }
    }
  }
  return {.row = row, .col = col};
}

template <typename T, std::size_t N>
linal::matrix<T, N + 1, 1> vec_insert(
    const linal::matrix<T, N, 1>& a, T value, std::size_t c
) {
  linal::matrix<T, N + 1, 1> result;
  for (std::size_t i = 0, ii = 0; i < N + 1; i++) {
    if (i == c) {
      result(i, 0) = value;
      continue;
    }
    result(i, 0) = a(ii, 0);
    ii++;
  }
  return result;
}

template <typename T, std::size_t N = 1>
linal::matrix<T, 1, 1> solve(
    const linal::matrix<T, 1, 1>& a,
    const linal::matrix<T, 1, 1>& b
) {
  auto result = linal::matrix<T, 1, 1>();
  result(0, 0) = b(0, 0) / a(0, 0);
  return result;
}

template <typename T, std::size_t N>
linal::matrix<T, N, 1> solve(
    const linal::matrix<T, N, N>& a,
    const linal::matrix<T, N, 1>& b
) {
  auto mx = find_max_by_abs(a);
  auto row = mx.row, col = mx.col;
  auto removed_row = linal::row(a[row]).without_col(col);
  auto next_a = a.without_row(row).without_col(col);
  auto next_b = b.without_row(row);

  for (std::size_t i = 0, next_i = 0; i < N; i++) {
    if (i == row) {
      continue;
    }
    auto m = a(i, col) / a(row, col);
    auto t = removed_row * m;
    next_a[next_i] -= linal::view(t);
    next_b(next_i, 0) -= b(i, 0) * m;
    next_i++;
  }

  auto sub = solve<T, N - 1>(next_a, next_b);
  auto res = vec_insert<T, N - 1>(sub, 0, row);

  auto x = b(row, 0);
  for (std::size_t j = 0; j < N - 1; j++) {
    x -= removed_row(0, j) * sub(j, 0);
  }
  res(row, 0) = x / a(row, col);

  return res;
}

}
}
}
}
