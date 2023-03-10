#pragma once
#include "math/linal/matrix.h"
#include <cstddef>
#include <functional>

namespace math {
namespace sle {
namespace method {
namespace gauss {

struct peek {
  std::size_t row;
  std::size_t col;
};

template <typename T>
peek peek_max_by_abs(const linal::matrix<T>& a) {
  std::size_t row = 0;
  std::size_t col = 0;
  for (std::size_t i = 0; i < a.rows_count(); i++) {
    for (std::size_t j = 0; j < a.cols_count(); j++) {
      if (std::abs(a(row, col)) < std::abs(a(i, j))) {
        row = i;
        col = j;
      }
    }
  }
  return {.row = row, .col = col};
}

template <typename T>
peek peek_top_left(const linal::matrix<T>& a) {
  return {.row = 0, .col = 0};
}

template <typename T, std::size_t N>
linal::fixed_matrix<T, N + 1, 1> vec_insert(
    const linal::fixed_matrix<T, N, 1>& a, T value, std::size_t c
) {
  linal::fixed_matrix<T, N + 1, 1> result;
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

template <typename T>
using element_peeker
    = std::function<peek(const linal::matrix<T>&)>;

template <typename T, std::size_t N> struct result {
  linal::fixed_matrix<T, N, 1> value;
  linal::fixed_matrix<T, N, 1> error;
  linal::fixed_matrix<T, N, N> a;
  linal::fixed_matrix<T, N, 1> b;
  T det;
};

template <typename T, std::size_t N = 1>
result<T, 1> solve(
    const linal::fixed_matrix<T, 1, 1>& a,
    const linal::fixed_matrix<T, 1, 1>& b,
    const element_peeker<T>& peek
) {
  auto result = linal::fixed_matrix<T, 1, 1>();
  result(0, 0) = b(0, 0) / a(0, 0);
  return {
      .value = result,
      .error = a * result - b,
      .a = a,
      .b = b,
      .det = a(0, 0),
  };
}

template <typename T, std::size_t N>
result<T, N> solve(
    const linal::fixed_matrix<T, N, N>& a,
    const linal::fixed_matrix<T, N, 1>& b,
    const element_peeker<T>& peek
) {
  auto mx = peek(a);
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
    next_b(next_i, 0) -= b(row, 0) * m;
    next_i++;
  }

  auto subres = solve<T, N - 1>(next_a, next_b, peek);
  auto result_x = vec_insert<T, N - 1>(subres.value, 0, row);

  auto x = b(row, 0);
  for (std::size_t j = 0; j < N - 1; j++) {
    x -= removed_row(0, j) * subres.value(j, 0);
  }
  result_x(row, 0) = x / a(row, col);

  auto zeroN = linal::fixed_matrix<T, 1, N - 1>::zero();
  auto zero1 = linal::fixed_matrix<T, 1, 1>::zero();
  auto triangle_row = linal::row(a[row]) * (1 / a(row, col));
  auto result_a = subres.a.with_col(col, view(zeroN))
                            .with_row(row, view(triangle_row));
  auto result_b = subres.b.with_row(row, view(zero1));
  result_b(row, 0) = b(row, 0) * (1 / a(row, col));
  return {
      .value = result_x,
      .error = result_a * result_x - result_b,
      .a = result_a,
      .b = result_b,
      .det = subres.det * a(row, col)
             * (((col + row) % 2 == 0) ? 1 : -1),
  };
}

}
}
}
}
