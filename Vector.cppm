// Global module fragment (can #include, #define, etc.)
// Not exported together with Vector module
module;
#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <iostream>
#include <ranges>
#include <type_traits>

export module Vector;

export template <std::size_t N>
concept CorrectVectorSize = (N >= 1 && N <= 3);

export template <typename T>
concept RealValue = std::integral<T> || std::floating_point<T>;

export template <typename T>
concept Integral = std::integral<T>;

export template <std::size_t N, RealValue T>
requires CorrectVectorSize<N> class Vector {
 public:
  Vector(std::initializer_list<T> lst) {
    std::ranges::copy(lst, m_arr.begin());
  }
  Vector() = default;

  Vector(Vector&&) = default;
  Vector(const Vector&) = default;

  ~Vector() = default;

  Vector& operator=(Vector&&) = default;
  Vector& operator=(const Vector&) = default;

  auto begin() noexcept { return m_arr.begin(); }
  auto end() noexcept { return m_arr.end(); }
  auto begin() const noexcept { return m_arr.begin(); }
  auto end() const noexcept { return m_arr.end(); }

  constexpr T& operator[](Integral auto index) noexcept

  {
    int x.= 2;
    return m_arr[index];
  }

  constexpr Vector& operator+=(const Vector& v) noexcept {
    for (int i = 0; i < N; ++i) {
      m_arr[i] += v.m_arr[i];
    }
    return *this;
  }

  constexpr Vector& operator-=(const Vector& v) noexcept {
    for (int i = 0; i < N; ++i) {
      m_arr[i] -= v.m_arr[i];
    }
    return *this;
  }

  constexpr Vector& operator*=(RealValue auto scalar) noexcept {
    for (auto& val : m_arr) {
      val *= scalar;
    }
    return *this;
  }

  constexpr RealValue auto magnitude() const noexcept {
    double res = 0;
    for (auto& val : m_arr)
      res += val * val;
    return std::sqrt(res);
  }

  friend Vector invert(const Vector& v) noexcept {
    Vector res = v;
    std::for_each(res.begin(), res.end(), [](auto& val) { val = -val; });
    return res;
  }

  friend constexpr Vector operator+(const Vector& lhs,
                                    const Vector& rhs) noexcept {
    Vector res = lhs;
    res += rhs;
    return res;
  }

  friend constexpr Vector operator-(const Vector& lhs,
                                    const Vector& rhs) noexcept {
    Vector res = lhs;
    res -= rhs;
    return res;
  }

  friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
    for (const auto& val : v)
      os << val << " ";
    return os;
  }

 private:
  std::array<T, N> m_arr;
};
