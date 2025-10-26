// Global module fragment (can #include, #define, etc.)
// Not imported together with your module
module;
#include <array>

export module Vector;

export template<int N, typename T>
class Vector
{
public:
    Vector& operator+=(const Vector&);
    Vector& operator-=(const Vector&);

private:
    T m_arr[N];
};

template<int N, typename T>
Vector<N, T>& Vector<N, T>::operator+=(const Vector<N, T>& v)
{
    // implement
}

template<int N, typename T>
Vector<N, T>& Vector<N, T>::operator-=(const Vector<N, T>& v)
{
    // implement
}
