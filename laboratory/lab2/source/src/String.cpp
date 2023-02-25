#include <iostream>
#include <cstring>
#include "../inc/String.hpp"

void String::print()
{
    for (size_t i = 0; i < m_size; i++)
    {
        std::cout << m_str[i];
    }
}
size_t String::length()
{
    return m_size;
}
int String::find(char *substr)
{
    char *res = strstr(m_str, substr);
    if (res)
    {
        return res - m_str;
    }
    return -1;
}

char const *String::c_str()
{
    return m_str;
}
char &String::at(size_t n)
{
    if (n >= m_size)
        throw std::out_of_range("Invalid index");
    return m_str[n];
}

// constructor
String::String(char const *str) : m_size(strlen(str)), m_str(new char[m_size + 1])
{
    std::copy(str, str + m_size, m_str);
    m_str[m_size] = 0;
}
String::String(const String &other) : String(other.m_str) {}
// operators
String &String::operator=(String tmp)
{
    std::swap(m_size, tmp.m_size);
    std::swap(m_str, tmp.m_str);
    return *this;
}
String String::operator+(const String &other)
{
    String tmp = *this;
    delete[] tmp.m_str;
    tmp.m_str = new char[(this->m_size + other.m_size + 1)];
    tmp.m_size = this->m_size + other.m_size + 1;
    std::copy(this->m_str, this->m_str + this->m_size + 1, tmp.m_str);
    //tmp.print();
    strcat(tmp.m_str, other.m_str);
    return tmp;
}
void String::operator+=(const String &other)
{
    String tmp = *this;
    delete[] this->m_str;
    this->m_str = new char[(tmp.m_size + other.m_size + 1)];
    this->m_size = this->m_size + other.m_size;
    std::copy(tmp.m_str, tmp.m_str + this->m_size, this->m_str);
    strcat(this->m_str, other.m_str);
}
char String::operator[](int index)
{
    return this->m_str[index];
}
bool String::operator>(const String &other)
{

    return (this->m_size) > (other.m_size);
}
bool String::operator<(const String &other)
{

    return (this->m_size) < (other.m_size);
}
bool String::operator==(const String &other)
{

    return ((this->m_size) == (other.m_size));
}
std::ostream &operator<<(std::ostream &stream,
                         String &tmp)
{
    tmp.print();
    return stream;
}
std::istream &operator>>(std::istream &stream,
                         String &tmp)
{
    char tmp_str[1000];
    stream >> tmp_str;
    delete[] tmp.m_str;
    tmp.m_str = new char[strlen(tmp_str) + 1];
    tmp.m_size = strlen(tmp_str);
    std::copy(tmp_str, tmp_str + strlen(tmp_str), tmp.m_str);
    return stream;
}
String::String(int str, size_t size){};
String::~String()
{
    std::cout << "Destructor" << std::endl;
    if (m_str)
    {
        delete[] m_str;
    }
};
