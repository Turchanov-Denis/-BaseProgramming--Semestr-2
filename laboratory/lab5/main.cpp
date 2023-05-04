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
            if (tmp_size == 8) {
                m_arr[m_capacity] = toByte(b);
                m_capacity++;
                tmp_size = 0;
            }
            b[tmp_size] = el;
            tmp_size++;
        }
        // add last to m_arr
        m_arr[m_capacity] = toByte(b);


    };

    MyBoolVector(MyBoolVector &other) {
        m_arr = new char[other.m_capacity];
        std::copy(other.m_arr, other.m_arr + m_size, m_arr);
        m_size = other.m_size;
        m_capacity = other.m_capacity;
    }

    ~MyBoolVector() {
        delete[] m_arr;
        std::cout << "-- Bye --" << std::endl;
    };

//    methods
    void push(int el) {
        m_size++;
        if ((m_size % 8) != 0) {
            if (el) {
                m_arr[m_capacity] |= 1 << ((m_size % 8) - 1);
            }
        } else {
            m_capacity++;
            m_arr[m_capacity] |= 1 << (m_size % 8);
        }

    }

    void push(bool el) {
        el = (unsigned int) el;
        m_size++;
        if ((m_size % 8) != 0) {
            if (el) {

                m_arr[m_capacity] |= 1 << ((m_size % 8) - 1);
            }
        } else {
            m_capacity++;
            m_arr[m_capacity] |= 1 << (m_size % 8);
        }
    }

    void print() {
        if (m_size <= 8) {
            unsigned int b[8]{0};
            fromByte(m_arr[m_capacity], b, m_size % 9, 1);
        } else {
            for (size_t i = 0; i <= m_capacity; i++) {
                unsigned int b[8]{0};
                fromByte(m_arr[i], b, 8, 1);
                std::cout << "----" << std::endl;
            }
        }
    }

    bool at(size_t index) {
        return (m_arr[index / 8]) & (1 << (index % 8));
    }
    size_t size() {
        return m_size;
    }
    void change(size_t index, bool el) {

        unsigned int b[8]{0};
        fromByte(m_arr[index / 8], b, 8);
        b[index%8] = int(el);
        m_arr[index / 8] = toByte(b);

    }

    void erase(size_t index) {
        if (m_size%8==0){
            m_capacity--;
        }
        for (size_t i = index; i < m_size; i++) {
            this->change(i, i+1);
        }
        m_size--;
    }
    void insert(size_t index, bool el) {
        if (m_size%8==0){
            m_capacity++;
        }
        m_size++;
//        std::cout << "awd "<< this->at(index) << std::endl;
        bool tmp = this->at(index);
        this->change(index,el);
        for (size_t i=index; i<m_size;i++){
            bool subTmp = this->at(i+1);
            this->change(i+1,tmp);
            tmp = subTmp;
        }

    }
};

int main() {
//    std::cout << 3/8 << std::endl;

    MyBoolVector<bool> a{1,0, 1, 1, 1, 1, 1,1};
//    MyBoolVector<bool> b{a};
//    a.push(false);
//    std::cout << a.at(2) << std::endl;
//    a.print();
//    a.insert(0, false);
//    a.erase(0);
    a.insert(7, false);
//    a.change(2, false);
    a.print();
//    std::cout << " ---- " << std::endl;
//    a.change(0, true);
//    a.print();
//    a.erase(1);

}