#pragma once
#include "vector.h"
#include <cstdint>

namespace linal {

template <typename T, std::size_t R, std::size_t C> class matrix {
public:
private:
  vector<vector<T, C>, R> content;
};

}; // namespace linal