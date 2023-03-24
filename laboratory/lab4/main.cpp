#include <iostream>

template <typename T, int N, int M>
class Matrix
{
private:
    T m_matrix[N][M];
    size_t m_stroke = N;
    size_t m_colomn = M;
    /* data */
    void Print()
    {
        for (size_t i = 0; i < m_stroke; i++)
        {
            if (i)
                std::cout << std::endl;
            for (size_t j = 0; j < m_colomn; j++)
            {
                std::cout << m_matrix[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
    void PrintS(int stroke, int colomn)
    {
        for (size_t i = 0; i < m_stroke; i++)
        {
            if (i)
                std::cout << std::endl;
            for (size_t j = 0; j < m_colomn; j++)
            {
                // if ((i <= stroke) || (j < colomn))
                // {
                //     std::cout << m_matrix[i][j] << " ";
                // }
                if ((i == stroke) && (j == colomn))
                {
                    std::cout << "."
                              << " ";
                }
                else
                {
                    std::cout << "-"
                              << " ";
                }
            }
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    void Input()
    {
        std::cout << "Enter element matrix:" << std::endl;
        for (size_t i = 0; i < m_colomn; i++)
        {
            // if (i)
            //     std::cout << std::endl;
            for (size_t j = 0; j < m_stroke; j++)
            {
                // std::cout << i << j << std::endl;
                PrintS(i, j);
                std::cin >> m_matrix[i][j];
            }
        }
        std::cout << std::endl;
    }

public:
    Matrix()
    {
        for (size_t i = 0; i < m_stroke; i++)
        {
            for (size_t j = 0; j < m_colomn; j++)
            {

                m_matrix[i][j] = 0;
            }
        }
    };
    Matrix(T *list, size_t len)
    {
        size_t m_len = len;
        for (size_t i = 0; i < m_stroke; i++)
        {
            for (size_t j = 0; j < m_colomn; j++)
            {
                if (m_len)
                {
                    m_matrix[i][j] = *list;
                    list++;
                    m_len--;
                }
                else
                {
                    m_matrix[i][j] = 0;
                }
            }
        }
    };

    // Matrix(const Matrix &tmp) : Matrix(tmp.m_matrix, m_stroke + m_colomn) {}
    Matrix &operator=(Matrix other)
    {
        std::swap(m_matrix, other.m_matrix);
        std::swap(m_stroke, other.m_stroke);
        std::swap(m_colomn, other.m_colomn);
        return *this;
    }
    Matrix &operator+=(const Matrix &tmp)
    {
        for (size_t i = 0; i < m_colomn; i++)
        {
            for (size_t j = 0; j < m_stroke; j++)
            {
                m_matrix[i][j] += tmp.m_matrix[i][j];
            }
        }
        return *this;
    }
    friend Matrix operator+(Matrix lhs, const Matrix &rhs)
    {
        lhs += rhs;
        return lhs;
    }
    Matrix &operator++()
    {
        for (size_t i = 0; i < m_colomn; i++)
        {
            for (size_t j = 0; j < m_stroke; j++)
            {
                m_matrix[i][j] += 1;
            }
        }
        return *this; // return new value by reference
    }

    // postfix increment
    Matrix operator++(int)
    {
        Matrix old = *this; // copy old value
        operator++();       // prefix increment
        return old;         // return old value
    }

    friend std::ostream &operator<<(std::ostream &out, Matrix &f)
    {
        f.Print();
        return out;
    }
    friend std::istream &operator>>(std::istream &input, Matrix &f)
    {
        f.Input();
        return input;
    }

    ~Matrix(){};
};

int main()
{
    // remake to array or vector
    int list[]{1, 2, 3, 4};
    int list1[]{1, 0, 0, 4};
    Matrix<int, 2, 2> T{list, 4};
    Matrix<int, 2, 2> T1{list1, 4};
    Matrix<int, 2, 2> T2 = T + T1;
    // T+=T1;
    T2++;
    std::cout << T2 << std::endl;
}