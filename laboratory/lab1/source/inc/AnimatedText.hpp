#include <iostream>
#include "windows.h"
class AnimatedText
{

private:
    int m_duration;
    std::string m_text;
    std::string m_is_animated_text = "";
 
public:
    AnimatedText(std::string text, unsigned int duration = 1000)
   {
        m_text = text;
        m_duration = duration;
    }

    AnimatedText(/* args */);
    ~AnimatedText(){};
    std::string  printAnimation()
    {
        if (m_is_animated_text.length() == m_text.length()) {
            return m_is_animated_text;
        }
        m_is_animated_text += m_text[m_is_animated_text.length()];
        return m_is_animated_text;
    }

    int getDuration() {
        return m_duration;
    }
};