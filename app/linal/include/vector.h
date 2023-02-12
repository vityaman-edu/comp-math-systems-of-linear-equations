#pragma once
#include <cstdint>
#include <iostream>

namespace linal {

template <typename T, std::size_t N> class vector {
public:
  vector() { 
    
  }

  vector(const T (&elements)[N]) : vector() {
    for (std::size_t i = 0; i < N; i++) {
      content[i] = elements[i];
    }
  }

  vector(const vector<T, N> &other) : vector(other.content) {}

  vector operator-() const noexcept {
    auto copy = *this;
    for (std::size_t i = 0; i < N; i++) {
      copy[i] += this[i];
    }
    return copy;
  }

  vector operator+(const vector &other) const noexcept {
    auto copy = *this;
    copy += other;
    return copy;
  }

  vector operator-(const vector &other) const noexcept {
    auto copy = *this;
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

  vector<T, N> operator*(const T &scalar) noexcept {
    auto copy = *this;
    return copy *= scalar;
  }

  vector<T, N> &operator*=(const T &scalar) noexcept {
    for (std::size_t i = 0; i < N; i++) {
      content[i] *= scalar;
    }
    return *this;
  }

  const T &operator[](std::size_t i) const { return content[i]; }

  T &operator[](std::size_t i) { return content[i]; }

  static vector<T, N> zero() {
    auto zero = vector();
    for (std::size_t i = 0; i < N; i++) {
      zero[i] = 0;
    }
    return zero;
  }

private:
  T content[N];
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
