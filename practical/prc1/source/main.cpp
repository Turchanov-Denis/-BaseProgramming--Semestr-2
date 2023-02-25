#include <iostream>
#include <vector>
class Typewriter
{
private:
    /* data */
    std::vector<std::string> v;
    size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
    {
        size_t pos = txt.find(ch);
        size_t initialPos = 0;
        strs.clear();

        // Decompose statement
        while (pos != std::string::npos)
        {
            strs.push_back(txt.substr(initialPos, pos - initialPos));
            initialPos = pos + 1;

            pos = txt.find(ch, initialPos);
        }

        // Add the last one
        strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

        return strs.size();
    }

public:
    Typewriter(const char *ptr)
    {
        split(ptr, v, ' ');
        std::cout<< v[0];
    };
    ~Typewriter(){};
};

int main()
{
    Typewriter tw("awd awd");
}