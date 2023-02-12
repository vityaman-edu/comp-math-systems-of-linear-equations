#pragma once
#include "vector.h"
#include <cstdint>

namespace linal {

template <typename T, std::size_t R, std::size_t C> class matrix {
private:
  typedef vector<T, C> row;

public:
  matrix() {}

  matrix(const T (&elements)[R][C]) : matrix() {
    for (std::size_t i = 0; i < R; i++) {
      for (std::size_t j = 0; j < C; j++) {
        content[i][j] = elements[i][j];
      }
    }
  }

  const row &operator[](std::size_t i) const { return content[i]; }

  row &operator[](std::size_t i) { return content[i]; }

  const vector<row, R>& as_vector() {
    return content;
  }

private:
  vector<row, R> content;
};



}; // namespace linal