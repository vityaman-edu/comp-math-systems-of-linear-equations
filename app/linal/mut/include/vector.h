#pragma once

namespace linal {
namespace mut {

template <typename T> class vector {
public:
  vector(std::size_t n) : n(n), data(new T[n]) {}
  vector(T *data, std::size_t n) : n(n), data(data) {}

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
      data[i] += other[i];
    }
    return *this;
  }

  vector<T, N> &operator-=(const vector<T, N> &other) noexcept {
    for (std::size_t i = 0; i < N; i++) {
      data[i] -= other[i];
    }
    return *this;
  }

  vector<T, N> operator*(const T &scalar) const noexcept {
    auto copy = *this;
    return copy *= scalar;
  }

  vector<T, N> &operator*=(const T &scalar) noexcept {
    for (std::size_t i = 0; i < N; i++) {
      data[i] *= scalar;
    }
    return *this;
  }

  const T &operator[](std::size_t i) const { return data[i]; }

  T &operator[](std::size_t i) { return data[i]; }

  static vector zero() {
    vector zero;
    for (std::size_t i = 0; i < n; i++) {
      for (std::size_t j = 0; j < n; j++) {
        zero[i][j] = 0;
      }
    }
    return zero;
  }

private:
  std::size_t n;
  T *data;
};

} // namespace mut
} // namespace linal
