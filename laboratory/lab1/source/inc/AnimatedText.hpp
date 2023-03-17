#include <iostream>

class AnimatedText
{

private:
    int m_duration;
    std::string m_text;
    std::string m_is_animated_text;
    long long int m_time_src{ 0 };

public:
    AnimatedText(std::string text = "", unsigned int duration = 1000)
    {
        m_text = text;
        m_duration = duration;
    }
    ~AnimatedText() {};
    /**
     * setText setup text animation
     *
     * @param string:
     */
    void setText(const std::string& str) {
        m_text = str;
        m_is_animated_text.resize(m_text.length());
    }
    /**
    * setDuration setup delay animation
    *
    * @param delay: in ms
    */
    void setDuration(int duration) {
        m_duration = duration;
    }
    /**
    * setSleepFunction setup metod of sleeping animation
    *
    * @param callback: is special sleep function
    */

    std::string  printAnimation()
    {

        //std::cout << m_is_animated_text.size() << " " << m_text.length() << std::endl;
        if (!m_time_src) {
            std::time_t result = std::time(nullptr);
            std::asctime(std::localtime(&result));
            m_time_src = result+1;

            /* std::cout << std::asctime(std::localtime(&result))
                 << result << " seconds since the Epoch\n" << typeid((long long int)result).name();*/

        }
        std::time_t result = std::time(nullptr);
        std::asctime(std::localtime(&result));
        return m_text.substr(0, (((result - m_time_src) / m_duration) % (m_text.length() +1)));
        
    }
private:
    void changeTmpText(char el) {
        m_is_animated_text += el;
    }
};