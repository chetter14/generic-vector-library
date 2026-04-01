#include <gtest/gtest.h>
#include <string>
#include <tuple>
#include <exception>
import Vector;

namespace {
/* Define plain struct type */
struct PlainStructValue {
  double x, y;
};

/* Define struct type with all the operators except '==' */
struct NoEqualityStructValue {
  double x;

  using value_type = decltype(x);

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
}  // namespace

TEST(Concepts, CorrectVectorSizeConcept) {
  static_assert(CorrectVectorSize<1>);
  static_assert(CorrectVectorSize<2>);
  static_assert(CorrectVectorSize<3>);
  static_assert(!CorrectVectorSize<0>);
  static_assert(!CorrectVectorSize<4>);
}

TEST(Concepts, RealTypeConcept) {
  static_assert(RealType<float>);
  static_assert(RealType<int>);
  static_assert(RealType<double>);
  static_assert(!RealType<std::string>);
  static_assert(!RealType<std::tuple<double, int>>);
}

TEST(Concepts, InvertibleConcept) {
  static_assert(Invertible<int>);
  static_assert(Invertible<double>);
  static_assert(!Invertible<std::string>);
}

TEST(Concepts, ArithmeticConcept) {
  static_assert(Arithmetic<int, int>);
  static_assert(Arithmetic<int, short>);
  static_assert(Arithmetic<short, int>);
  static_assert(Arithmetic<double, int>);
  static_assert(Arithmetic<int, double>);
  static_assert(!Arithmetic<int, std::string>);
  static_assert(!Arithmetic<std::string, int>);
  static_assert(!Arithmetic<CorrectStructValue, int>);
  static_assert(!Arithmetic<int, CorrectStructValue>);
}

TEST(Concepts, VectorElementTypeConcept) {
  static_assert(VectorElementType<double>);
  static_assert(VectorElementType<unsigned char>);
  static_assert(!VectorElementType<std::string>);
  static_assert(!VectorElementType<PlainStructValue>);
  static_assert(!VectorElementType<NoEqualityStructValue>);
  static_assert(VectorElementType<CorrectStructValue>);
}

TEST(Concepts, ScalableWithConcept) {
  static_assert(ScalableWith<double, int>);
  static_assert(ScalableWith<int, double>);
  static_assert(!ScalableWith<std::string, int>);
  static_assert(!ScalableWith<double, std::string>);
  static_assert(ScalableWith<CorrectStructValue, double>);
  static_assert(ScalableWith<CorrectStructValue, int>);
  static_assert(!ScalableWith<CorrectStructValue, std::string>);
}

TEST(MathVector, EmptyInit) {
  /* Vector<0, int> v1;     Compile error! */
  Vector<1, int> v1;
  Vector<2, int> v2;
  Vector<3, int> v3;
  /* Vector<4, int> v4;     Compile error! */
}

TEST(MathVector, InitWithWrongListSize) {
  try {
    Vector<1, int> v{1, 2};
    FAIL() << "Expected std::length_error";
  }
  catch (const std::length_error& ex) {
    EXPECT_STREQ(ex.what(),
                 "The initializer list size does not match vector dimensions!");
  }

  try {
    Vector<3, int> v{1, 2};
    FAIL() << "Expected std::length_error";
  } 
  catch (const std::length_error& ex) {
    EXPECT_STREQ(ex.what(),
                 "The initializer list size does not match vector dimensions!");
  }

  Vector<1, int> v1{1};
  Vector<2, int> v2{1, 2};
  Vector<3, int> v3{1, 2, 3};
}
