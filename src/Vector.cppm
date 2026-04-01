// Global module fragment (can #include, #define, etc.)
// Not exported together with Vector module
module;
#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <type_traits>

export module Vector;

export template <std::size_t N>
concept CorrectVectorSize = (N >= 1 && N <= 3);

export template <typename T>
concept RealType = std::integral<T> || std::floating_point<T>;

export template <typename T>
concept Invertible = requires(T x) {
  -x;
};

export template <typename T, typename U>
concept Arithmetic = requires(T x, U y) {
  x + y;
  x - y;
  x += y;
  x -= y;
};

export template <typename T>
concept Printable = requires(T x, std::ostream os) {
  os << x;
};

export template <typename T>
concept Comparable = requires(T x, T y) {
  x <=> y;
};

export template <typename T>
concept Movable = requires(T x, T y) {
  x = std::move(y);
  T{std::move(x)};
};

export template <typename T>
concept VectorElementType =
    std::regular<T> && Invertible<T> && Arithmetic<T, T> && Printable<T>;

export template <typename T, typename U>
concept ScalableWith = requires(T elem, U scalar) {
  elem *= scalar;
};

export template <std::size_t N, VectorElementType T>
requires CorrectVectorSize<N> class Vector {
 public:
  using value_type = T;

  constexpr Vector(std::initializer_list<T> lst) {
    if (lst.size() != N) {
      throw std::length_error(
          "The initializer list size does not match vector dimensions!");
    }
    std::ranges::copy(lst, m_arr.begin());
  }
  constexpr Vector() : m_arr() {}
  constexpr Vector(const Vector& v) : m_arr(v.m_arr) {}
  constexpr Vector(Vector&& v) : m_arr(std::move(v.m_arr)) {}

  auto begin() noexcept { return m_arr.begin(); }
  auto end() noexcept { return m_arr.end(); }
  auto begin() const noexcept { return m_arr.begin(); }
  auto end() const noexcept { return m_arr.end(); }

  constexpr T& operator[](std::size_t index) {
    if (index >= N)
      throw std::out_of_range("Vector index is out of range!");
    return m_arr[index];
  }

  constexpr const T& operator[](std::size_t index) const {
    if (index >= N)
      throw std::out_of_range("Vector index is out of range!");
    return m_arr[index];
  }

  constexpr Vector& operator+=(const Vector& v) noexcept(
      noexcept(std::declval<T&>() += std::declval<T&>())) {
    std::ranges::transform(m_arr, v, m_arr.begin(),
                           [](const auto& a, const auto& b) { return a + b; });
    return *this;
  }

  constexpr Vector& operator-=(const Vector& v) noexcept(
      noexcept(std::declval<T&>() += std::declval<T&>())) {
    std::ranges::transform(m_arr, v, m_arr.begin(),
                           [](const auto& a, const auto& b) { return a - b; });
    return *this;
  }

  constexpr Vector& operator*=(RealType auto scalar) noexcept(
      noexcept(std::declval<T&>() *=
               scalar)) requires ScalableWith<T, decltype(scalar)> {
    std::for_each(m_arr.begin(), m_arr.end(),
                  [scalar](auto& val) { val *= scalar; });
    return *this;
  }

  constexpr Vector operator-() const {
    Vector res = *this;
    std::for_each(res.begin(), res.end(), [](auto& val) { val = -val; });
    return res;
  }

  void dump(std::ostream& os) const {
    std::for_each(m_arr.begin(), m_arr.end(),
                  [&](auto val) { os << val << " "; });
  }

 private:
  std::array<T, N> m_arr;
};

export template <std::size_t N, VectorElementType T>
std::ostream& operator<<(std::ostream& os, const Vector<N, T>& v) {
  v.dump(os);
  return os;
}

export template <std::size_t N, typename T>
constexpr Vector<N, T> operator+(const Vector<N, T>& lhs,
                                 const Vector<N, T>& rhs) noexcept {
  Vector res = lhs;
  res += rhs;
  return res;
}

export template <std::size_t N, typename T>
constexpr Vector<N, T> operator-(const Vector<N, T>& lhs,
                                 const Vector<N, T>& rhs) noexcept {
  Vector res = lhs;
  res -= rhs;
  return res;
}