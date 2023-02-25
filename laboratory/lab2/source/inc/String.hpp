#include <iostream>
#include <cstring>

class String
{
private:
    size_t m_size;
    char *m_str = nullptr;

public:
    // metod
    void print(){}
    size_t length(){}
    int find(char *substr){}
    char const *c_str(){}
    char &at(size_t n){}

    // constructor
    String(char const *str) : m_size(strlen(str)), m_str(new char[m_size + 1]){}
    String(const String &other) : String(other.m_str) {}
    // operators
    String &operator=(String tmp){}
    String operator+(const String &other){}
    void operator+=(const String &other){}
    char operator[](int index){}
    bool operator>(const String &other){}
    bool operator<(const String &other){}
    bool operator==(const String &other){}
    friend std::ostream &operator<<(std::ostream &stream,
                                    String &tmp){}
    friend std::istream &operator>>(std::istream &stream,
                                    String &tmp){}
    String(int str, size_t size) = delete;
    ~String(){};
};
