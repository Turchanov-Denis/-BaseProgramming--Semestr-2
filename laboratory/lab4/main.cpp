#include <iostream>

template<typename T, int N, int M>
class Matrix {
private:
    T m_data[N][M];

public:
    Matrix() {}

    Matrix(const Matrix &other) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                m_data[i][j] = other.m_data[i][j];
            }
        }
    }

    Matrix &operator=(const Matrix &other) {
        if (this != &other) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    m_data[i][j] = other.m_data[i][j];
                }
            }
        }
        return *this;
    }

    friend std::istream &operator>>(std::istream &is, Matrix &matrix) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                is >> matrix.m_data[i][j];
            }
        }
        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                os << matrix.m_data[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

    Matrix operator+(const Matrix &other) const {
        Matrix result;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                result.m_data[i][j] = m_data[i][j] + other.m_data[i][j];
            }
        }
        return result;
    }

    Matrix &operator+=(const Matrix &other) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                m_data[i][j] += other.m_data[i][j];
            }
        }
        return *this;
    }

    template<int P>
    Matrix<T, N, P> operator*(const Matrix<T, M, P> &other) const {
        Matrix<T, N, P> result;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < P; j++) {
                result.m_data[i][j] = 0;
                for (int k = 0; k < M; k++) {
                    result.m_data[i][j] += m_data[i][k] * other.m_data[k][j];
                }
            }
        }
        return result;
    }
    Matrix &operator*=(const Matrix &other) {
        *this = *this * other;
        return *this;
    }

    Matrix &operator++() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                m_data[i][j]++;
            }
        }
        return *this;
    }

    T determinant() const {
        if (N!=M){
            throw std::exception();
        }

        if (N == 1) {
            return m_data[0][0];
        }

        T det = 0;
        Matrix<T, N - 1, M - 1> subMatrix;

        for (int i = 0; i < N; i++) {
            int subI = 0;
            for (int j = 1; j < N; j++) {
                int subJ = 0;
                for (int k = 0; k < M; k++) {
                    if (k != i) {
                        subMatrix.m_data[subI][subJ] = m_data[j][k];
                        subJ++;
                    }
                }
                subI++;
            }

            T subDet = subMatrix.determinant();
            if (i % 2 == 0) {
                det += m_data[0][i] * subDet;
            } else {
                det -= m_data[0][i] * subDet;
            }
        }

        return det;
    }

    const T &operator()(int i, int j) const {
        return m_data[i][j];
    }
};

int main() {
    Matrix<int, 3, 3> matrix1;
    Matrix<int, 3, 3> matrix2;
    std::cin >> matrix1;
    std::cin >> matrix2;
    auto sum = matrix1 + matrix2;
    std::cout << "Sum: " << std::endl;
    std::cout << sum << std::endl;

    matrix1 += matrix2;
    std::cout << "Multiply 1" << std::endl;
    std::cout << matrix1 << std::endl;

    auto product = matrix1 * matrix2;
    std::cout << "Multiply 1 and 2" << std::endl;
    std::cout << product << std::endl;
    std::cout << "awd" << std::endl;
    product*=matrix2;
    std::cout << matrix1 << std::endl;
}