#pragma once
#include "vector.h"
#include <cstdint>

namespace linal {

template <typename T, std::size_t R, std::size_t C>
class matrix : public vector<vector<T, C>, R> {
public:
  matrix() {}

  matrix(const T (&elements)[R][C]) : matrix() {
    for (std::size_t i = 0; i < R; i++) {
      (*this)[i] = vector<T, C>(elements[i]);
    }
  }

  matrix operator*(const T &scalar) noexcept {
    matrix copy = *this;
    copy *= scalar;
    return copy;
  }

  matrix &operator*=(const T &scalar) noexcept {
    for (std::size_t i = 0; i < R; i++) {
      (*this)[i] *= scalar;
    }
  }

  void apply_inplace(vector<T, C> &vector) const noexcept {
    for (std::size_t i = 0; i < C; i++) {
      vector[i] = combine((*this)[i], vector);
    }
  }

  static matrix zero() {
    matrix zero;
    for (std::size_t i = 0; i < R; i++) {
      for (std::size_t j = 0; j < C; j++) {
        zero[i][j] = 0;
      }
    }
    return zero;
  }

  static matrix id() {
    matrix id = zero();
    for (std::size_t i = 0; i < R; i++) {
      id[i][i] = 1;
    }
    return id;
  }
};

}; // namespace linal