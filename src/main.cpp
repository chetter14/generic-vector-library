#include <iostream>
#include <string>
#include <tuple>
import Vector;

int main() {
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

  auto inv_v1 = -v1;
  std::cout << "v1 - " << v1 << std::endl;
  std::cout << "inv_v1 - " << inv_v1 << std::endl;
  
  { 
    Vector<3, short> v3{1, 2, 3};
    Vector<3, short> v4{5, 6, 7};

    std::cout << "v3 - " << v3 << std::endl;
    std::cout << "v4 - " << v4 << std::endl;

    auto sum_v = v3 + v4;
    std::cout << "sum_v - " << sum_v << std::endl;

    v3 += v4;
    v3 *= 2;
    std::cout << v3 << std::endl;
  }

  {
    /* Different size:
    Vector<1, short> v4;
    Vector<2, short> v5;

    v4 + v5;  
    Compile error!
    */
  }

  {
    /* Different type: 
    Vector<2, short> v4;
    Vector<2, double> v5;

    v4 + v5;
    v4 - v5;
    Compile error !
    */
  }

  return 0;
}
