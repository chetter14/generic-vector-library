#include <iostream>
#include <string>
import Vector;

int main()
{
    Vector<2, float> v1;
    Vector<2, float> v2;

    v1 += v2;

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

    Vector<2, double> v4 {3.1, 9.5};
    std::cout << v4 << std::endl;

    std::cout << "It works!" << std::endl;
    return 0;
}
