#pragma once
#include <array>
#include <cstdint>
#include <iostream>

namespace linal {

template <typename T, std::size_t N> class vector {
public:
  vector(const std::array<T, N> &content) : content(content) {
    std::cout << "Vector<" << N << "> created" << std::endl;
  }

  vector(const vector<T, N> &other) : vector(other.content) {}

  vector operator-() const noexcept {
    vector<T, N> copy = *this;
    for (std::size_t i = 0; i < N; i++) {
      copy[i] += this[i];
    }
    return copy;
  }

  vector operator+(const vector &other) const noexcept {
    vector<T, N> copy = *this;
    copy += other;
    return copy;
  }

  vector operator-(const vector &other) const noexcept {
    vector<T, N> copy = *this;
    copy -= other;
    return copy;
  }

  vector &operator+=(const vector &other) noexcept {
    for (std::size_t i = 0; i < N; i++) {
      content[i] += other[i];
    }
    return *this;
  }

  vector<T, N> &operator-=(const vector<T, N> &other) noexcept {
    for (std::size_t i = 0; i < N; i++) {
      content[i] -= other[i];
    }
    return *this;
  }

  const T &operator[](std::size_t i) const { return content[i]; }
  T &operator[](std::size_t i) { return content[i]; }

private:
  std::array<T, N> content;
};

template <typename T, std::size_t N>
std::ostream &operator<<(std::ostream &stream, const vector<T, N> &vector) {
  stream << "{ ";
  for (std::size_t i = 0; i < N - 1; i++) {
    stream << vector[i] << ", ";
  }
  if (N > 0) {
    stream << vector[N - 1];
  }
  stream << " }";
  return stream;
}

}; // namespace linal
