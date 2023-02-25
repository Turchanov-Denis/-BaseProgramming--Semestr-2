#include <iostream>
#include <cstring>
#include "inc/String.hpp"

int main()
{
    String s1("Hello");
    String s2(s1);
    std::cout << "assignment s2:" << s2 << std::endl;
    String s3 = s1;
    std::cout << "copy assignment s3:" << s3 << std::endl;
    String s4 = s1 + s2;
    std::cout << "operator + s4:" << s4 << std::endl;
    s3 += s1;
    std::cout << "operator += s3:" << s3 << std::endl;
    std::cout << "operator [] s3:" << s3[0] << std::endl;
    std::cout << "s3:" << s3 << " s4: " << s4 << " operator >,<,== " << (s1 == s2) << std::endl;
    
    
    // s1.print();
} 