#include <iostream>
#include <string>
#include <tuple>
import Vector;

void test_concepts();

int main() {
  test_concepts();

  Vector<2, int> v1;
  Vector<2, int> v2;

  // Vector<0, double> my_v1;
  Vector<1, double> my_v2;
  Vector<3, double> my_v3;
  // Vector<5, double> my_v4;

  Vector<3, short> another_v;

  // Vector<2, std::string> str_v;

  v1 += v2;

  v1 *= 2.3;

  v1[0];

  v1 + v2;
  v1 - v2;

  Vector<3, double> v3;
  v3[0] = 2.0;
  v3[1] = 4.0;
  v3[2] = 6.0;

  auto inv_v3 = invert(v3);
  std::cout << v3 << std::endl;
  std::cout << inv_v3 << std::endl;
  //   std::cout << v3.magnitude() << std::endl;

  Vector<2, double> v4{3.1, 9.5};
  std::cout << v4 << std::endl;

  const Vector<2, double> v5{3.4, 8.5};
  std::cout << v5 << std::endl;

  std::cout << "It works!" << std::endl;
  return 0;
}

struct PlainStructValue {
  double x, y;
};

struct NoEqualityStructValue {
  double x;

  friend double operator+(NoEqualityStructValue& lhs,
                          NoEqualityStructValue& rhs) {
    return 0.0;
  }
  friend double operator-(NoEqualityStructValue& lhs,
                          NoEqualityStructValue& rhs) {
    return 0.0;
  }

  double operator+=(NoEqualityStructValue& obj) { return 0.0; }
  double operator-=(NoEqualityStructValue& obj) { return 0.0; }

  double operator+() { return 0.0; }
  double operator-() { return 0.0; }

  friend std::ostream& operator<<(std::ostream& os,
                                  NoEqualityStructValue& obj) {
    return os;
  }

  friend int operator<=>(const NoEqualityStructValue& lhs, 
                         const NoEqualityStructValue& rhs) {
    return 0;
  }
};

struct CorrectStructValue : public NoEqualityStructValue {
  friend bool operator==(const NoEqualityStructValue& lhs,
                         const NoEqualityStructValue& rhs) {
    return false;
  }
};

void test_concepts() {
  static_assert(CorrectVectorSize<1>);
  static_assert(CorrectVectorSize<2>);
  static_assert(CorrectVectorSize<3>);
  static_assert(!CorrectVectorSize<0>);
  static_assert(!CorrectVectorSize<4>);

  static_assert(RealType<float>);
  static_assert(RealType<int>);
  static_assert(RealType<double>);
  static_assert(!RealType<std::string>);
  static_assert(!RealType<std::tuple<double, int>>);

  static_assert(Indexable<int>);
  static_assert(Indexable<char>);
  static_assert(!Indexable<float>);
  static_assert(!Indexable<std::string>);

  static_assert(!ElementType<PlainStructValue>);
  static_assert(!ElementType<NoEqualityStructValue>);
  static_assert(ElementType<CorrectStructValue>);
}