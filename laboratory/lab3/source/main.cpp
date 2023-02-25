#include <iostream>

class Complex
{
private:
    double m_a;
    double m_b;

public:
    explicit Complex(double a = 0.0, double b = 0.0) : m_a(a), m_b(b) {}
    Complex(const Complex &tmp) {}
    Complex& operator=(Complex tmp)
    {
        std::swap(m_a, tmp.m_a);
        std::swap(m_b, tmp.m_b);
    }
    Complex& operator+=(const Complex &other)
    {
        this->m_a += other.m_a;
        this->m_b += other.m_b;
        return *this;
    }
    friend Complex operator+(Complex self, const Complex &other)
    {
        self += other;
        return self;
    }
};

int main()
{
}