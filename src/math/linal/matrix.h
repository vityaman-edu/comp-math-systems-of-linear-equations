#pragma once
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>

namespace math {
namespace linal {

template <typename T, std::size_t N> class row_view {
public:
  // Note: don't use it
  row_view(T* data) : data(data) {}

  row_view<T, N>& operator=(row_view<T, N> other) noexcept {
    for (std::size_t i = 0; i < N; i++) {
      data[i] = other.data[i];
    }
    return *this;
  }

  row_view<T, N>& operator-=(row_view<T, N> other) noexcept {
    for (std::size_t i = 0; i < N; i++) {
      data[i] -= other.data[i];
    }
    return *this;
  }

  const T& operator[](std::size_t i) const { return data[i]; }

  T& operator[](std::size_t i) { return data[i]; }

private:
  T* data;
};

template <typename T, std::size_t R, std::size_t C>
class matrix {
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

  matrix<T, R - 1, C> without_row(std::size_t r) const noexcept {
    matrix<T, R - 1, C> result;
    for (std::size_t i = 0, ii = 0; i < R; i++) {
      if (i == r) {
        continue;
      }
      result[ii] = (*this)[i];
      ii++;
    }
    return result;
  }

  matrix<T, R, C - 1> without_col(std::size_t c) const noexcept {
    return this->transposed().without_row(c).transposed();
  }

  const row_view<T, C> operator[](std::size_t i) const {
    return row_view<T, C>((T*)data[i]);
  }

  row_view<T, C> operator[](std::size_t i) {
    return row_view<T, C>((T*)data[i]);
  }

  matrix<T, C, R> transposed() const noexcept {
    matrix<T, C, R> result;
    for (std::size_t i = 0; i < R; i++) {
      for (std::size_t j = 0; j < C; j++) {
        result(j, i) = data[i][j];
      }
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

private:
  T data[R][C];
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
operator<<(std::ostream& stream, const row_view<T, N>& row) {
  stream << "{ ";
  for (std::size_t i = 0; i < N - 1; i++) {
    stream << row[i] << ", ";
  }
  if (N > 0) {
    stream << row[N - 1];
  }
  stream << " }";
  return stream;
}

template <typename T, std::size_t N>
row_view<T, N> view(matrix<T, 1, N>& row) {
  return row[0];
}

template <typename T, std::size_t N>
matrix<T, N, 1> column(row_view<T, N> view) {
  matrix<T, N, 1> column;
  for (std::size_t i = 0; i < N; i++) {
    column(i, 0) = view[i];
  }
  return column;
}

template <typename T, std::size_t N>
matrix<T, 1, N> row(row_view<T, N> view) {
  return column(view).transposed();
}

} // namespace linal
} // namespace math