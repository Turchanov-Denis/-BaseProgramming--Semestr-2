#include <iostream>

template <typename T>
class MyBoolVector{};


template <>
class MyBoolVector<bool>
{
private:
    /* data */
    char* m_arr;
    size_t m_size{};

    unsigned char toByte(unsigned char b[8])
    {
        unsigned char c = 0;
        for (int i = 0; i < 8; ++i)
            if (b[i])
                c |= 1 << i;
        return c;
    }

    void fromByte(unsigned char c, unsigned char b[8])
    {
        for (int i = 0; i < 8; ++i)
            b[i] = (c & (1 << i)) != 0;
    }

public:
    MyBoolVector(std::initializer_list<int> arr){
        std::cout << arr.size() << std::endl;

        m_arr = new char[arr.size()];

        m_size = arr.size();
    };
    ~MyBoolVector(){
        delete[] m_arr;
        std::cout << "Bye" << std::endl;
    };
};

int main()
{
    MyBoolVector<bool> a{1,0,1};
}