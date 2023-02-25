#include <iostream>
#include <cstring>
//#include "../inc/String.hpp"
class String
{
private:
    size_t m_size;
    char *m_str = nullptr;

public:
    // metod
    void print()
    {
        for (size_t i = 0; i < m_size; i++)
        {
            std::cout << m_str[i];
        }
    }
    size_t length()
    {
        return m_size;
    }
    int find(char *substr)
    {
        char *res = strstr(m_str, substr);
        if (res)
        {
            return res - m_str;
        }
        return -1;
    }

    char const *c_str()
    {
        return m_str;
    }
    char &at(size_t n)
    {
        if (n >= m_size)
            throw std::out_of_range("Invalid index");
        return m_str[n];
    }

    // constructor
    String(char const *str) : m_size(strlen(str)), m_str(new char[m_size + 1])
    {
        std::copy(str, str + m_size, m_str);
        m_str[m_size] = 0;
    }
    String(const String &other) : String(other.m_str) {}
    // operators
    String &operator=(String tmp)
    {
        std::swap(m_size, tmp.m_size);
        std::swap(m_str, tmp.m_str);
        return *this;
    }
    String operator+(const String &other)
    {
        String tmp = *this;
        delete[] tmp.m_str;
        tmp.m_str = new char[(this->m_size + other.m_size + 1)];
        tmp.m_size = this->m_size + other.m_size + 1;
        std::copy(this->m_str, tmp.m_str + this->m_size, tmp.m_str);
        // tmp.print();
        strcat(tmp.m_str, other.m_str);
        return tmp;
    }
    void operator+=(const String &other)
    {
        String tmp = *this;
        delete[] this->m_str;
        this->m_str = new char[(tmp.m_size + other.m_size + 1)];
        this->m_size = this->m_size + other.m_size + 1;
        std::copy(tmp.m_str, tmp.m_str + this->m_size, this->m_str);
        strcat(this->m_str, other.m_str);
    }
    char operator[](int index)
    {
        return this->m_str[index];
    }
    bool operator>(const String &other)
    {

        return (this->m_size) > (other.m_size);
    }
    bool operator<(const String &other)
    {

        return (this->m_size) < (other.m_size);
    }
    bool operator==(const String &other)
    {

        return (this->m_size) == (other.m_size);
    }
    friend std::ostream &operator<<(std::ostream &stream,
                                    String &tmp)
    {
        tmp.print();
    }
    friend std::istream &operator>>(std::istream &stream,
                                    String &tmp)
    {
        char tmp_str[1000];
        stream >> tmp_str;
        delete[] tmp.m_str;
        tmp.m_str = new char[strlen(tmp_str) + 1];
        tmp.m_size = strlen(tmp_str);
        std::copy(tmp_str, tmp_str + strlen(tmp_str), tmp.m_str);
    }
    String(int str, size_t size) = delete;
    ~String()
    {
        std::cout << "Destructor" << std::endl;
        if (m_str)
        {
            delete[] m_str;
        }
    };
};
