#include <iostream>
#include <cstring>
#include "inc/String.hpp"

int main()
{
    String s1("Hello");
    String s2("World");
    // s1 += s2;

    std::cout << s2.at(3) << std::endl;
    // s1.print();
}