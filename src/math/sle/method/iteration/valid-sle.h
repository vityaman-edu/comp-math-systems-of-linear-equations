#pragma once
#include "math/linal/matrix.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <set>
#include <stdexcept>
#include <iostream>

namespace math {
namespace sle {
namespace method {
namespace iteration {

template <typename T, std::size_t N>
static T sum_by_abs(const linal::matrix<T, 1, N>& vector) {
  T sum = 0;
  for (std::size_t i = 0; i < N; i++) {
    sum += std::fabs(vector(0, i));
  }
  return sum;
}

template <typename T, std::size_t N> class valid_sle {
private:
  linal::matrix<T, N, N> a;
  linal::matrix<T, N, 1> b;

public:
  const linal::matrix<T, N, N>& left() const noexcept {
    return a;
  }

  const linal::matrix<T, N, 1>& right() const noexcept { return b; }

  static valid_sle make(
      const linal::matrix<T, N, N>& a,
      const linal::matrix<T, N, 1>& b
  ) {
    std::set<std::size_t> row_candidates[N];
    for (std::size_t i = 0; i < N; i++) {
      row_candidates[i] = std::set<std::size_t>();
    }

    for (std::size_t i = 0; i < N; i++) {
      auto row = a.row_at(i);
      T row_abs_sum = sum_by_abs(row);
      for (std::size_t j = 0; j < N; j++) {
        if (row_abs_sum <= 2 * std::fabs(row(0, j))) {
          row_candidates[j].insert(i);
        }
      }
    }

    std::size_t indexes[N];
    for (std::size_t i = 0; i < N; i++) {
      indexes[i] = i;
    }
    auto less_by_candidates_count =
        [row_candidates](std::size_t i, std::size_t j) {
          return row_candidates[i].size() <
                 row_candidates[j].size();
        };
    std::sort(indexes, indexes + N, less_by_candidates_count);

    std::size_t suitable[N];
    std::set<std::size_t> used_rows;
    for (std::size_t i = 0; i < N; i++) {
      const auto& candidates = row_candidates[indexes[i]];

      std::set<std::size_t> diff;
      std::set_difference(
          candidates.begin(),
          candidates.end(),
          used_rows.begin(),
          used_rows.end(),
          std::inserter(diff, diff.end())
      );

      if (diff.size() == 0) {
        throw std::invalid_argument(
            "matrix can't be made diagonal predominant"
        );
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
      result.a.row_set(i, a.row_at(suitable[i]));
      result.b(i, 0) = b(suitable[i], 0);
    }
    return result;
  }
};

} // namespace iteration
} // namespace method
} // namespace sle
} // namespace math