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
    /**
     * setText setup text animation
     *
     * @param string:
     */
    void setText(const std::string& str) {
        m_text = str;
    }
     /**
     * setDuration setup delay animation
     *
     * @param delay: in ms
     */
    void setDuration( int duration) {
        m_duration = duration;
    }
    /**
    * setSleepFunction setup metod of sleeping animation
    *
    * @param callback: is special sleep function
    */
    void setSleepFunction(void (*callback)(int)) {
        m_sleep = callback;
    }
    std::string  printAnimation() 
    {
        if (m_sleep == nullptr) {
            throw std::runtime_error{ " Sleep function not exist && setup it " };
        }
        if (m_is_animated_text.length() == m_text.length()) {
            return m_is_animated_text;
        }
        changeTmpText(m_text[m_is_animated_text.length()]);
        m_sleep((m_duration));
        return m_is_animated_text;
    }
private:
    void changeTmpText(char el) {
        m_is_animated_text += el;
    }
};