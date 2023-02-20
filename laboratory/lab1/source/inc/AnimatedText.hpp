#include <iostream>
#include "windows.h"
class AnimatedText
{

private:
    int m_duration;
    std::string m_text;
    std::string m_is_animated_text = "";
    void (*m_sleep)(int);

public:
    AnimatedText(std::string text="", unsigned int duration = 1000, void (*callback)(int) = nullptr)
    {
        m_text = text;
        m_duration = duration;
        m_sleep = callback;
    }
    ~AnimatedText() {};
    void setText(std::string str) {
        m_text = str;
    }
    void setDuration( int duration) {
        m_duration = duration;
    }
    void setSleepFunction(void (*callback)(int)) {
        m_sleep = callback;
    }
    std::string  printAnimation()
    {
        if (m_is_animated_text.length() == m_text.length()) {
            return m_is_animated_text;
        }
        m_is_animated_text += m_text[m_is_animated_text.length()];
        m_sleep((m_duration));
        return m_is_animated_text;
    }
};