// Global module fragment (can #include, #define, etc.)
// Not imported together with your module
module;
#include <array>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <ranges>
#include <type_traits>

export module Vector;

export template<int N, typename T>
class Vector
{
public:
    Vector(std::initializer_list<T> lst) 
    {
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

    constexpr T& operator[](int index) noexcept;
    
    constexpr Vector& operator+=(const Vector&) noexcept;
    constexpr Vector& operator-=(const Vector&) noexcept;

    constexpr Vector& operator*=(int scalar) noexcept;

    constexpr double magnitude() const noexcept;

    // TO-DO: check how it works, fix implementation
    friend Vector invert(const Vector& v) noexcept
    {
        Vector res = v;
        std::for_each(res.begin(), res.end(), [](auto& val){ val = -val; });
        return res;
    }

    friend constexpr Vector operator+(const Vector& lhs, const Vector& rhs) noexcept
    {
        Vector res = lhs;
        res += rhs;
        return res;
    }

    friend constexpr Vector operator-(const Vector& lhs, const Vector& rhs) noexcept
    {
        Vector res = lhs;
        res -= rhs;
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& v)
    {
        for (const auto& val : v)
            os << val << " ";
        return os;
    }

private:
    std::array<T, N> m_arr;
};

template<int N, typename T>
constexpr T& Vector<N, T>::operator[](int index) noexcept
{
    return m_arr[index];
}

template<int N, typename T>
constexpr Vector<N, T>& Vector<N, T>::operator+=(const Vector<N, T>& v) noexcept
{
    for (int i = 0; i < N; ++i) {
        m_arr[i] += v.m_arr[i];
    }
    return *this;
}

template<int N, typename T>
constexpr Vector<N, T>& Vector<N, T>::operator-=(const Vector<N, T>& v) noexcept
{
    for (int i = 0; i < N; ++i) {
        m_arr[i] -= v.m_arr[i];
    }
    return *this;
}

template<int N, typename T>
constexpr Vector<N, T>& Vector<N, T>::operator*=(int scalar) noexcept
{
    for (auto& val : m_arr) {
        val *= scalar;
    }
    return *this;
}

template<int N, typename T>
constexpr double Vector<N, T>::magnitude() const noexcept
{
    double res = 0;
    for (auto& val : m_arr)
        res += val * val;
    return std::sqrt(res);
}