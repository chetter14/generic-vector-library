#include <iostream>
#include <string>
import Vector;

int main()
{
    Vector<2, float> v1;
    Vector<1, std::string> v2;

    v1 += v1;

    std::cout << "It works!" << std::endl;
    return 0;
}
