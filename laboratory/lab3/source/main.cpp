#include <iostream>

class Complex
{
private:
    double m_a;
    double m_b;

public:
    explicit Complex(double a = 0.0, double b = 0.0) : m_a(a), m_b(b) {}
    Complex(const Complex &tmp)
    {
        m_a = tmp.m_a;
        m_b = tmp.m_b;
    }
    Complex &operator=(Complex tmp)
    {
        std::cout << " Copy operator " << std::endl;
        std::swap(m_a, tmp.m_a);
        std::swap(m_b, tmp.m_b);
        return *this;
    }
    Complex &operator+=(const Complex &other)
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
    Complex &operator*=(const Complex &other)
    {
        this->m_a *= other.m_a;
        this->m_b *= other.m_b;
        return *this;
    }
    friend Complex operator*(Complex self, const Complex &other)
    {
        self *= other;
        return self;
    }
    ~Complex() {}
    Complex &operator++()
    {
        this->m_a += 1;
        return *this;
    }
    Complex &operator--()
    {
        this->m_a -= 1;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const Complex &f)
    {
        return out << f.m_a << " + " << f.m_b << "i";
    }

    friend std::istream &operator<<(std::istream &in, Complex &f)
    {
        in >> f.m_a >> f.m_b;
    }
};

int main()
{
    Complex c1(1.0, 2.0), c2(2.0);
    Complex c3 = c1 + c2;
    std::cout << c3;
}