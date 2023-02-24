#pragma once
#include "vector.h"

namespace linal {
namespace mut {

template <typename T> class matrix {
public:
  matrix(std::size_t n, std::size_t m) : n(n), m(m), data(new T[n * m]) {}

  vector operator[](std::size_t i) { return vector(data + i * m, m); }

private:
  std::size_t n;
  std::size_t m;
  T *data;
};

} // namespace mut
} // namespace linal