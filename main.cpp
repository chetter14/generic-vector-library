#include <iostream>
#include <string>
#include <tuple>
import Vector;

void test_concepts();

int main() {
  test_concepts();

  Vector<2, double> v1;
  const Vector<2, double> v2{1.0, 1.0};

  for (auto& val : v1) {
    val = 1.0;
  }

  std::cout << "v1 - " << v1 << std::endl;
  std::cout << "v2 - " << v2 << std::endl;

  v1 += v2;
  std::cout << "v1 - " << v1 << std::endl;

  v1 *= 2.3;
  std::cout << "v1 - " << v1 << std::endl;

  v1[0] = -7.7;
  std::cout << "v1 - " << v1 << std::endl;

  std::cout << "v1 + v2: " << v1 + v2 << std::endl;
  std::cout << "v1 - v2: " << v1 - v2 << std::endl;

  auto inv_v1 = invert(v1);
  std::cout << "v1 - " << v1 << std::endl;
  std::cout << "inv_v1 - " << inv_v1 << std::endl;

  const Vector<3, int> v3;

  return 0;
}

/* Define plain struct type */
struct PlainStructValue {
  double x, y;
};

/* Define struct type with all the operators except '==' */
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

  friend int operator<=>
      (const NoEqualityStructValue& lhs, const NoEqualityStructValue& rhs) {
    return 0;
  }
};

/* Do define operators '==' and '*=' and so we got correct vector type */
struct CorrectStructValue : public NoEqualityStructValue {
  friend bool operator==(const NoEqualityStructValue& lhs,
                         const NoEqualityStructValue& rhs) {
    return false;
  }

  double operator*=(RealType auto scalar) { return 0.0; }
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

  static_assert(VectorElementType<double>);
  static_assert(VectorElementType<unsigned char>);
  static_assert(!VectorElementType<std::string>);
  static_assert(!VectorElementType<PlainStructValue>);
  static_assert(!VectorElementType<NoEqualityStructValue>);
  static_assert(VectorElementType<CorrectStructValue>);

  static_assert(ScalableWith<double, int>);
  static_assert(ScalableWith<int, double>);
  static_assert(!ScalableWith<std::string, int>);
  static_assert(!ScalableWith<double, std::string>);
  static_assert(ScalableWith<CorrectStructValue, double>);
  static_assert(ScalableWith<CorrectStructValue, int>);
  static_assert(!ScalableWith<CorrectStructValue, std::string>);
}