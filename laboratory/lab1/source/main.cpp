#include <iostream>
#include "inc/AnimatedText.h"
int main()
{

    // std::string text = "awd";
    AnimatedText thing{"awd", 10000};
    thing.printAnimation();
}