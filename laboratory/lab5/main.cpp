#include <iostream>

template<typename T>
class MyBoolVector {
};


template<>
class MyBoolVector<bool> {
private:
    /* data */
    char *m_arr;
    size_t m_capacity{};
    size_t m_size{};

    unsigned char toByte(unsigned int b[8]) {
        unsigned char c{0};
        for (int i = 0; i < 8; ++i)
            if (b[i])
                c |= 1 << i;
        return c;
    }

    void fromByte(unsigned char c, unsigned int b[8], size_t size, int flag = 0) {

        for (int i = 0; i < size; ++i) {
            b[i] = (c & (1 << i)) != 0;
            if (flag)
                std::cout << b[i] << std::endl;
        }
    }

public:
    MyBoolVector() = default;

    MyBoolVector(std::initializer_list<int> arr) {
//        std::cout << arr.size() << std::endl;
        m_arr = new char[arr.size() / 4];
        m_size = arr.size(); // in bit
        unsigned int b[8]{0};
        int tmp_size{};
        for (int el: arr) {
            if (tmp_size == 7) {
                m_arr[m_capacity] = toByte(b);
                m_capacity++;
                tmp_size = 0;
            }
            b[tmp_size] = el;
            tmp_size++;
        }
        // add last to m_arr
        m_arr[m_capacity] = toByte(b);

        fromByte(m_arr[m_capacity], b, m_size % 8);
    };

    MyBoolVector(MyBoolVector &other) {
        m_arr = new char[other.m_capacity];
        std::copy(other.m_arr, other.m_arr + m_size, m_arr);
        m_size = other.m_size;
        m_capacity = other.m_capacity;
    }

    ~MyBoolVector() {
        delete[] m_arr;
        std::cout << "Bye" << std::endl;
    };

//    methods
    void push(int el) {
        m_size++;
        std::cout <<" a1 " <<m_arr[m_capacity] << std::endl;
        if ((m_size % 8) != 0) {
            if (el) {
                m_arr[m_capacity] |= 1 << (m_size % 8);
                std::cout<<" a2 " << m_arr[m_capacity] << std::endl;
            }
            else {}
        } else {
            m_capacity++;
            m_arr[m_capacity] |= 1 << (m_size % 8);
        }

    }

    void push(bool el) {
        el = (unsigned int) el;
        m_size++;
//        std::cout <<" 1 w" <<m_arr[m_capacity] << std::endl;
        if ((m_size % 8) != 0) {
            if (el) {

                m_arr[m_capacity] |= 1 << ((m_size % 8) - 1 );
//                std::cout<<" w2 " << m_arr[m_capacity] << std::endl;
            }
        } else {
            m_capacity++;
            m_arr[m_capacity] |= 1 << (m_size % 8);
        }
    }

    void print() {
        for (size_t i = 1; i < m_capacity; i++) {
            unsigned int b[8]{0};
            fromByte(m_arr[i], b, 8, 1);
        }
        unsigned int b[8]{0};
        fromByte(m_arr[m_capacity], b, m_size % 8, 1);
    }
};

int main() {
    MyBoolVector<bool> a{1, 0, 1};
//    MyBoolVector<bool> b{a};
    a.push(false);
    a.push(true);
    a.push(false);
    a.print();

}