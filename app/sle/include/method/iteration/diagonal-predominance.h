#pragma once
#include "app/linal/include/matrix.h"
#include "app/linal/include/vector.h"
#include <cmath>
#include <stdexcept>

namespace sle {
namespace method {
namespace iteration {

template <typename T, std::size_t N>
static T sum_by_abs(const linal::vector<T, N> vector) {
  T sum = 0;
  for (std::size_t i = 0; i < N; i++) {
    sum += std::abs(vector[i]);
  }
  return sum;
}

template <typename T, std::size_t N>
static bool has_diagonal_predominance(const linal::matrix<T, N, N> &matrix) {
  for (std::size_t i = 0; i < N; i++) {
    if (2 * std::abs(matrix[i][i]) < sum_by_abs(matrix[i])) {
      return false;
    }
  }
  return true;
}

template <typename T, std::size_t N>
class diagonal_predominant_matrix : public linal::matrix<T, N, N> {
private:
  diagonal_predominant_matrix(const linal::matrix<T, N, N> &other)
      : linal::matrix<T, N, N>(other) {}

public:
  static diagonal_predominant_matrix make(const linal::matrix<T, N, N> &other) {
    if (!has_diagonal_predominance(other)) {
      throw std::invalid_argument("matrix has not diagonal predominance");
    }
    return diagonal_predominant_matrix<T, N>(other);
  }
};

} // namespace iteration
} // namespace method
} // namespace sle