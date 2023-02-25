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
  max_by_abs_result<T> result = {.row = 0, .col = 0};
  for (std::size_t i = 0; i < N; i++) {
    for (std::size_t j = 0; j < N; j++) {
      if (result.value < std::abs(a(i, j))) {
        result = {.row = i, .col = j};
      }
    }
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
  auto row = mx.i, col = mx.j;
  auto removed_row = a.row_at(row).without_col(col);
  auto next_a = a.without_row(row).without_col(col);
  auto next_b = b.without_col(row);

  for (std::size_t i = 0, next_i = 0; i < N; i++) {
    if (i == row) {
      continue;
    }
    auto m = (a[i][col] / mx.value);
    std::cout << "m(" << b[i] << ") = " << m << std::endl;
    next_a[next_i] -= removed_row * m;
    next_b[next_i] -= b(i, 0) * m;
    next_i++;
  }
}

}
}
}
}
