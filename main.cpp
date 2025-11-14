#include <iostream>
#include <string>
import Vector;

int main() {
  static_assert(CorrectVectorSize<1>);
  static_assert(CorrectVectorSize<2>);
  static_assert(CorrectVectorSize<3>);
  static_assert(!CorrectVectorSize<0>);
  static_assert(!CorrectVectorSize<4>);

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
  std::cout << v3.magnitude() << std::endl;

  Vector<2, double> v4{3.1, 9.5};
  std::cout << v4 << std::endl;

  const Vector<2, double> v5{3.4, 8.5};
  std::cout << v5 << std::endl;

  std::cout << "It works!" << std::endl;
  return 0;
}
