#pragma once
#include "vector.h"
#include <cstdint>

namespace linal {

template <typename T, std::size_t R, std::size_t C>
class matrix : public vector<vector<T, C>, R> {
public:
  matrix() {}

  matrix(const T& value) : matrix() {
    for (std::size_t i = 0; i < R; i++) {
      (*this)[i] = 0;
    }
  }

  matrix(const T (&elements)[R][C]) : matrix() {
    for (std::size_t i = 0; i < R; i++) {
      (*this)[i] = vector<T, C>(elements[i]);
    }
  }


};

}; // namespace linal