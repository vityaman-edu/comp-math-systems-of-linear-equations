#pragma once
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>

namespace math {
namespace linal {

template <typename T, std::size_t R, std::size_t C>
class matrix {

public:
  T data[R][C];

public:
  matrix() {
    for (std::size_t i = 0; i < R; i++) {
      for (std::size_t j = 0; j < C; j++) {
        data[i][j] = 0;
      }
    }
  }

  matrix(const matrix<T, R, C>& other) {
    for (std::size_t i = 0; i < R; i++) {
      for (std::size_t j = 0; j < C; j++) {
        data[i][j] = other(i, j);
      }
    }
  }

  matrix<T, R, C> operator-(const matrix<T, R, C>& other
  ) const noexcept {
    matrix<T, R, C> result = *this;
    result -= other;
    return result;
  }

  void operator-=(const matrix<T, R, C>& other) noexcept {
    for (std::size_t i = 0; i < R; i++) {
      for (std::size_t j = 0; j < C; j++) {
        data[i][j] -= other(i, j);
      }
    }
  }

  matrix<T, R, C> operator*(const T& k) const noexcept {
    matrix<T, R, C> result = *this;
    result *= k;
    return result;
  }

  void operator*=(const T& k) noexcept {
    for (std::size_t i = 0; i < R; i++) {
      for (std::size_t j = 0; j < C; j++) {
        data[i][j] *= k;
      }
    }
  }

  matrix<T, R, C> operator+(const matrix<T, R, C>& other
  ) const noexcept {
    matrix<T, R, C> result = *this;
    result += other;
    return result;
  }

  void operator+=(const matrix<T, R, C>& other) noexcept {
    for (std::size_t i = 0; i < R; i++) {
      for (std::size_t j = 0; j < C; j++) {
        data[i][j] += other(i, j);
      }
    }
  }

  const T& operator()(std::size_t i, std::size_t j) const {
    return data[i][j];
  }

  T& operator()(std::size_t i, std::size_t j) {
    return data[i][j];
  }

  void
  row_set(std::size_t i, const matrix<T, 1, C>& row) noexcept {
    for (std::size_t j = 0; j < C; j++) {
      data[i][j] = row(0, j);
    }
  }

  matrix<T, 1, C> row_at(std::size_t i) const {
    matrix<T, 1, C> result;
    for (std::size_t j = 0; j < C; j++) {
      result(0, j) = data[i][j];
    }
    return result;
  }

  static matrix<T, R, C> zero() noexcept {
    matrix<T, R, C> zero;
    for (std::size_t i = 0; i < R; i++) {
      for (std::size_t j = 0; j < C; j++) {
        zero(i, j) = 0;
      }
    }
    return zero;
  }
};

template <
    typename T,
    std::size_t R,
    std::size_t C,
    std::size_t N>
matrix<T, R, N> operator*(
    const matrix<T, R, C>& left, const matrix<T, C, N>& right
) noexcept {
  matrix<T, R, N> result;
  for (std::size_t i = 0; i < R; i++) {
    for (std::size_t j = 0; j < N; j++) {
      result(i, j) = 0;
      for (std::size_t k = 0; k < C; k++) {
        result(i, j) += left(i, k) * right(k, j);
      }
    }
  }
  return result;
}

template <typename T, std::size_t N>
std::ostream&
operator<<(std::ostream& stream, const matrix<T, N, 1>& vector) {
  // stream << "{ ";
  for (std::size_t i = 0; i < N - 1; i++) {
    stream << vector(i, 0) << ", ";
  }
  if (N > 0) {
    stream << vector(N - 1, 0);
  }
  // stream << " }";
  return stream;
}

} // namespace linal
} // namespace math