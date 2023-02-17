#include <iostream>
#include "windows.h"
class AnimatedText
{

private:
    std::string m_text;
    unsigned int m_duration;

public:
    AnimatedText(std::string text, unsigned int duration = 1000)
    {
        m_text = text;
        m_duration = duration;
    }

    AnimatedText(/* args */);
    ~AnimatedText(){};
    void printAnimation()
    {
        for (size_t i = 0; i < m_text.length(); i++)
        {
            std::cout << m_text[i];
            Sleep(m_duration);
        }
    }
};