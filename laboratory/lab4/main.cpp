#include <iostream>
#include <cmath>
template <typename T, int N, int M>
class Matrix
{
private:
    T m_matrix[N][M];
    size_t m_stroke = N;
    size_t m_colomn = M;
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
                T x;
                std::cin >> x;
                m_matrix[i][j] = x;
            }
        }
        std::cout << std::endl;
    }
    void clearMemory(int **a, int n)
    { // Функция освобождения памяти, выделенной под двумерный динамический массив
        for (int i = 0; i < n; i++)
        {
            delete[] a[i];
        }
        delete[] a;
    }
    int findDet(int **a, int n)
    { // Рекурсивная функция вычисления определителя матрицы
        if (n == 1)
            return a[0][0];
        else if (n == 2)
            return a[0][0] * a[1][1] - a[0][1] * a[1][0];
        else
        {
            int d = 0;
            for (int k = 0; k < n; k++)
            {
                int **m = new int *[n - 1];
                for (int i = 0; i < n - 1; i++)
                {
                    m[i] = new int[n - 1];
                }
                for (int i = 1; i < n; i++)
                {
                    int t = 0;
                    for (int j = 0; j < n; j++)
                    {
                        if (j == k)
                            continue;
                        m[i - 1][t] = a[i][j];
                        t++;
                    }
                }
                d += pow(-1, k + 2) * a[0][k] * findDet(m, n - 1);
                clearMemory(m, n - 1); // Освобождаем память, выделенную под алгебраическое дополнение
            }
            return d; // Возвращаем определитель матрицы
        }
    }

public:
    T get(int n, int m)
    {
        return m_matrix[n - 1][m - 1];
    }
    void change(int n, int m)
    {
        T x;
        std::cin >> x;
        m_matrix[n - 1][m - 1] = x;
    }
    T Detr()
    {
        if ((std::is_same_v<T, int>) || (std::is_same_v<T, double>) || (std::is_same_v<T, float>))
        {
            int **a = new int *[m_stroke]; // Объявляем двумерный целочисленный динамический массив (матрицу)
            for (int i = 0; i < m_stroke; i++)
            {
                a[i] = new int[m_stroke];
            }
            for (int i = 0; i < m_stroke; i++)
            {
                for (int j = 0; j < m_stroke; j++)
                {
                    a[i][j] = m_matrix[i][j]; // Вводим элементы матрицы
                }
            }
            return findDet(a, m_stroke);
        }
        if (std::is_same_v<T, std::string>)
        {
            // concatinate logic
        }
        return -9999;
    }
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

    Matrix &operator*=(const Matrix &tmp)
    {
        T tmp_matrix[m_stroke][tmp.m_colomn];
        for (size_t i = 0; i < m_stroke; i++)
        {
            for (size_t j = 0; j < m_stroke; j++)
            {
                tmp_matrix[i][j] = 0;
                for (size_t k = 0; k < m_stroke; k++)
                {
                    tmp_matrix[i][j] = m_matrix[i][k] * tmp.m_matrix[k][j];
                    // std::cout << m_matrix[i][k] << tmp.m_matrix[k][j] << std::endl;
                }
            }
        }
        for (size_t i = 0; i < m_stroke; i++)
        {
            for (size_t j = 0; j < m_colomn; j++)
            {
                m_matrix[i][j] = tmp_matrix[i][j];
            }
        }
        std::cout << std::endl;
        return *this;
    }
    friend Matrix operator*(Matrix lhs, const Matrix &rhs)
    {
        lhs *= rhs;
        return lhs;
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
    double list[]{1, 2, 3, 4, 1, 6, 7, 8, 9};
    int list1[]{1, 0, 0, 4};
    Matrix<double, 3, 3> T{list, 9};
    Matrix<int, 2, 2> T1{list1, 4};
    // --------------
    // Matrix<int, 2, 2> T2 = T + T1;
    // T+=T1;
    // T2++;
    // std::cout << T2 << std::endl;
    // --------------
    // std::cout << T << std::endl;
    // std::cout << T1 << std::endl;
    // Matrix<int, 2, 2> T2 = T * T1;
    // std::cout << T2 << std::endl;
    // --------------------------
    std::cout << T << std::endl;
    std::cout << T.Detr() << std::endl;
    // --------------------------
    // std::cout << T << std::endl;
    // T.change(1, 1);
    // std::cout << T << std::endl;
    // std::cout << T.get(1, 2) << std::endl;
}