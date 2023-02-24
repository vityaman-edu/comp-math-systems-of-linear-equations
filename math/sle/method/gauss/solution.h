#pragma once
#include "math/linal/matrix.h"
#include "math/linal/vector.h"
#include <cmath>
#include <iostream>

namespace sle {
namespace method {
namespace gauss {

template <typename T, std::size_t R, std::size_t C>
linal::matrix<T, R - 1, C>
remove_row(const linal::matrix<T, R, C>& a, std::size_t r) {
  linal::matrix<T, R - 1, C> result;
  for (std::size_t i = 0, ii = 0; i < R; i++) {
    if (i == r) {
      continue;
    }
    for (std::size_t j = 0; j < C; j++) {
      result[ii][j] = a[i][j];
    }
    ii++;
  }
  return result;
}

template <typename T, std::size_t R, std::size_t C>
linal::matrix<T, R, C - 1> remove_column(
    const linal::matrix<T, R, C>& a, std::size_t c
) {
  linal::matrix<T, R, C - 1> result;
  for (std::size_t i = 0; i < R; i++) {
    for (std::size_t j = 0, jj = 0; j < C; j++) {
      if (j == c) {
        continue;
      }
      result[i][jj] = a[i][j];
      jj++;
    }
  }
  return result;
}

template <typename T, std::size_t N>
linal::vector<T, N - 1> vec_remove_column(
    const linal::vector<T, N>& a, std::size_t c
) {
  linal::vector<T, N - 1> result;
  for (std::size_t i = 0, ii = 0; i < N; i++) {
    if (i == c) {
      continue;
    }
    result[ii] = a[i];
    ii++;
  }
  return result;
}

template <typename T, std::size_t N>
linal::vector<T, N + 1> vec_insert_column(
    const linal::vector<T, N>& a, T value, std::size_t c
) {
  linal::vector<T, N + 1> result;
  for (std::size_t i = 0, ii = 0; i < N + 1; i++) {
    if (i == c) {
      result[i] = value;
      continue;
    }
    result[i] = a[ii];
    ii++;
  }
  return result;
}

template <typename T> struct max_by_abs_result {
  T value;
  std::size_t i;
  std::size_t j;
};

template <typename T, std::size_t N>
max_by_abs_result<T>
find_max_by_abs(const linal::matrix<T, N, N>& a) {
  max_by_abs_result<T> result = {
      .value = a[0][0], .i = 0, .j = 0};
  for (std::size_t i = 0; i < N; i++) {
    for (std::size_t j = 0; j < N; j++) {
      if (result.value < std::abs(a[i][j])) {
        result = {.value = a[i][j], .i = i, .j = j};
      }
    }
  }
  return result;
}

template <typename T, std::size_t N> struct result {
  linal::vector<T, N> value;
};

template <typename T, std::size_t N = 1>
result<T, 1> solve(
    const linal::matrix<T, 1, 1>& a,
    const linal::vector<T, 1>& b
) {
  T v[1] = {b[0] / a[0][0]};
  return {.value = linal::vector<T, 1>(v)};
}

template <typename T, std::size_t N>
result<T, N> solve(
    const linal::matrix<T, N, N>& a,
    const linal::vector<T, N>& b
) {
  auto mx = find_max_by_abs(a);
  auto row = vec_remove_column(a[mx.i], mx.j);
  auto next = remove_column(remove_row(a, mx.i), mx.j);
  auto nres = vec_remove_column(b, mx.i);
  for (std::size_t i = 0, ii = 0; i < N; i++) {
    if (i == mx.i) {
      continue;
    }
    auto m = (a[i][mx.j] / mx.value);
    std::cout << "m(" << b[i] << ") = " << m << std::endl;
    next[ii] -= row * m;
    nres[ii] -= b[i] * m;
    ii++;
  }

  if (N < 5) {
    std::cout << next << std::endl;
    std::cout << nres << std::endl;
    std::cout << row << std::endl;
  }

  auto subres = solve<T, N - 1>(next, nres);
  std::cout << "subres = " << subres.value << std::endl;
  auto res =
      vec_insert_column<T, N - 1>(subres.value, 0.0, mx.i);
  auto x = b[mx.i];
  for (std::size_t j = 0; j < N; j++) {
    x -= row[j] * res[j];
  }
  res[mx.i] = x;
  std::cout << "res = " << res << std::endl;
  return {.value = res};
}
} // namespace gauss
} // namespace method
} // namespace sle