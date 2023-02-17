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
static T sum_by_abs(const linal::vector<T, N> &vector) {
  T sum = 0;
  for (std::size_t i = 0; i < N; i++) {
    sum += std::fabs(vector[i]);
  }
  return sum;
}

template <typename T, std::size_t N> class valid_sle {
private:
  linal::matrix<T, N, N> a;
  linal::vector<T, N> b;

public:
  const linal::matrix<T, N, N> &left() const noexcept { return a; }

  const linal::vector<T, N> &right() const noexcept { return b; }

  static valid_sle make(const linal::matrix<T, N, N> &a,
                        const linal::vector<T, N> &b) {
    std::set<std::size_t> row_candidates[N];
    for (std::size_t i = 0; i < N; i++) {
      row_candidates[i] = std::set<std::size_t>();
    }

    for (std::size_t i = 0; i < N; i++) {
      const auto &row = a[i];
      T row_abs_sum = sum_by_abs(row);
      for (std::size_t j = 0; j < N; j++) {
        if (row_abs_sum <= 2 * std::fabs(row[j])) {
          row_candidates[j].insert(i);
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

    std::size_t suitable[N];
    std::set<std::size_t> used_rows;
    for (std::size_t i = 0; i < N; i++) {
      const auto &candidates = row_candidates[indexes[i]];

      std::set<std::size_t> diff;
      std::set_difference(candidates.begin(), candidates.end(),
                          used_rows.begin(), used_rows.end(),
                          std::inserter(diff, diff.end()));

      if (diff.size() == 0) {
        throw std::invalid_argument(
            "matrix can't be made diagonal predominant");
      }

      std::size_t candidate;
      for (auto c : diff) {
        candidate = c;
        break;
      }

      used_rows.insert(candidate);
      suitable[indexes[i]] = candidate;
    }

    valid_sle<T, N> result;
    for (std::size_t i = 0; i < N; i++) {
      result.a[i] = a[suitable[i]];
      result.b[i] = b[suitable[i]];
    }
    return result;
  }
};

} // namespace iteration
} // namespace method
} // namespace sle