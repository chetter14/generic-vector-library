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
concept Invertable = requires(T x) {
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
concept Streamable = requires(T x, std::ostream& os) {
  os << x;
};

export template <typename T>
concept Comparable = requires(T x, T y) {
  x == y;
  x != y;
  x > y;
  x >= y;
  x < y;
  x <= y;
};

export template <typename T>
concept Movable = requires(T x, T y) {
  x = std::move(y);
  T{std::move(x)};
};

export template <typename T>
concept VectorElementType =
    std::regular<T> && Invertable<T> && Arithmetic<T, T> && Streamable<T> &&
    Comparable<T> && Movable<T>;

export template <typename T, typename U>
concept ScalableWith = requires(T elem, U scalar) {
  elem *= scalar;
};

export template <std::size_t N, VectorElementType T>
requires CorrectVectorSize<N> class Vector {
 public:
  using value_type = T;

  Vector(std::initializer_list<T> lst) {
    if (lst.size() != N) {
      throw std::invalid_argument(
          "Initializer list size does not match vector dimension!");
    }
    std::ranges::copy(lst, m_arr.begin());
  }
  Vector() : m_arr{} {}

  Vector(Vector&&) = default;
  Vector(const Vector&) = default;

  ~Vector() = default;

  Vector& operator=(Vector&&) = default;
  Vector& operator=(const Vector&) = default;

  auto begin() noexcept { return m_arr.begin(); }
  auto end() noexcept { return m_arr.end(); }
  auto begin() const noexcept { return m_arr.begin(); }
  auto end() const noexcept { return m_arr.end(); }

  constexpr T& operator[](std::size_t index) {
    if (index < 0 || index >= N)
      throw std::out_of_range("Vector index is out of range!");
    return m_arr[index];
  }

  constexpr const T& operator[](std::size_t index) const {
    if (index < 0 || index >= N)
      throw std::out_of_range("Vector index is out of range!");
    return m_arr[index];
  }

  template <typename U>
  constexpr Vector& operator+=(const Vector<N, U>& v) noexcept requires
      Arithmetic<T, U> {
    for (int i = 0; i < N; ++i) {
      m_arr[i] += v[i];
    }
    return *this;
  }

  template <typename U>
  constexpr Vector& operator-=(const Vector<N, U>& v) noexcept requires
      Arithmetic<T, U> {
    for (int i = 0; i < N; ++i) {
      m_arr[i] -= v[i];
    }
    return *this;
  }

  constexpr Vector& operator*=(RealType auto scalar) noexcept requires
      ScalableWith<T, decltype(scalar)> {
    for (auto& val : m_arr) {
      val *= scalar;
    }
    return *this;
  }

  //   constexpr RealValue auto magnitude() const noexcept {
  //     double res = 0;
  //     for (auto& val : m_arr)
  //       res += val * val;
  //     return std::sqrt(res);
  //   }

  friend Vector invert(const Vector& v) noexcept {
    Vector res = v;
    std::for_each(res.begin(), res.end(), [](auto& val) { val = -val; });
    return res;
  }

  template <typename U>
  friend constexpr Vector operator+(const Vector& lhs,
                                    const Vector<N, U>& rhs) noexcept requires
      Arithmetic<T, U> {
    Vector res = lhs;
    res += rhs;
    return res;
  }

  template <typename U>
  friend constexpr Vector operator-(const Vector& lhs,
                                    const Vector<N, U>& rhs) noexcept requires
      Arithmetic<T, U> {
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
