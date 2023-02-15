#pragma once
#include "app/linal/include/matrix.h"
#include "app/linal/include/vector.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <set>
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
  diagonal_predominant_matrix() : linal::matrix<T, N, N>() {} 

  diagonal_predominant_matrix(const linal::matrix<T, N, N> &other)
      : linal::matrix<T, N, N>(other) {}

public:
  static diagonal_predominant_matrix make(const linal::matrix<T, N, N> &other) {
    std::set<std::size_t> row_candidates[N];
    for (std::size_t i = 0; i < N; i++) {
      row_candidates[i] = std::set<std::size_t>();
    }

    for (std::size_t i = 0; i < N; i++) {
      const auto &row = other[i];
      T row_abs_sum = sum_by_abs(row);
      for (std::size_t j = 0; j < N; j++) {
        if (row_abs_sum <= 2 * std::abs(row[j])) {
          row_candidates[i].insert(j);
        }
      }
    }

    std::size_t indexes[N];
    for (std::size_t i = 0; i < N; i++) {
      indexes[i] = i;
    }
    auto less_by_candidates_count = [row_candidates](std::size_t i,
                                                     std::size_t j) {
      return row_candidates[i].size() < row_candidates[j].size();
    };
    std::sort(indexes, indexes + N, less_by_candidates_count);

    std::set<std::size_t> used_rows;
    for (std::size_t i = 0; i < N; i++) {
      const auto &candidates = row_candidates[indexes[i]];

      std::set<std::size_t> diff;
      std::set_difference(candidates.begin(), candidates.end(),
                          used_rows.begin(), used_rows.end(),
                          std::inserter(diff, diff.end()));

      if (diff.size() == 0) {
        throw std::invalid_argument("matrix can't make diagonal predominance");
      }

      auto candidate = *diff.begin();
      used_rows.insert(candidate);
      indexes[i] = candidate;
    }

    diagonal_predominant_matrix<T, N> result;
    for (std::size_t i = 0; i < N; i++) {
      result[i] = other[indexes[i]];
    }
    return result;
  }
};

} // namespace iteration
} // namespace method
} // namespace sle