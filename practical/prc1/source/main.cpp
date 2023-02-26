#include <iostream>
#include <vector>
class Typewriter
{
private:
    /* data */
    std::vector<std::string> v;
    int *m_arr = nullptr;
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
    void setKey(int *arr)
    {
        int tmp[] = {2, 8, 5, 1, 3};
        // for (size_t i=0; i < v.size(); i++)
        // {
        //     std::cin>> arr[i];
        // }
        for (size_t i = 0; i < v.size(); i++)
        {
            arr[i] = tmp[i];
        }
    }
    int fibo(int n)
    {
        if (n == 1 || n == 2)
            return (n - 1);
        return fibo(n - 1) + fibo(n - 2);
    }
    int fibo_index(int value)
    {
        for (int i = 3; i < 10; i++)
        {
            if (value == fibo(i))
            {
                return i - 3;
            }
        }
        throw std::out_of_range("awd");
    }

public:
    Typewriter(const char *ptr)
    {
        m_arr = new int[split(ptr, v, ' ')];
        std::cout << "words: " << v.size() << std::endl;
        setKey(m_arr);
    };
    ~Typewriter()
    {
        delete[] m_arr;
    };

    void Encode()
    {
        for (size_t i = 0; i < v.size(); i++)
        {
            std::cout << v[fibo_index(m_arr[i])] << std::endl;
        }
    }
    void Decode()
    {
        for (size_t i = 0; i < v.size(); i++) // find pos fibo by self fibo
        {
            for (size_t j = 0; j < v.size(); j++)
            {
                if (fibo_index(m_arr[j]) == i)
                {
                    std::cout << v[j] << " ";
                }
            }
        }
    }
};

int main()
{
    // Typewriter tw("Hello, my name is Ivan.");
    // tw.Encode();
    Typewriter tw1("my Ivan. is Hello, name");
    tw1.Decode();
}