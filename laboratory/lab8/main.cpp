#include <iostream>
#include <stdexcept>

template<typename T>
class Stack {
private:
    T *m_data;
    int capacity;
    int topIndex;

public:
    Stack(int size) : capacity(size), topIndex(0) {
        m_data = new T[capacity];

    }

    int size() const {
        return topIndex;
    }

    bool empty() const {
        return !topIndex;
    }

    void push(const T &item) {
        if (topIndex == capacity) {
            std::cout << "Stack overflow. Cannot push more items." << std::endl;
            throw std::overflow_error("Stack overflow");
        }
        m_data[++topIndex] = item;
    }

    T pop() {
        if (empty()) {
            std::cout << "Stack is empty. Cannot pop an item." << std::endl;
            throw std::out_of_range("Stack is empty");
        }
        return m_data[topIndex--];
    }

    T top() const {
        bool a = empty();
        if (empty()) {
            std::cout << "Stack is empty. Cannot get top item." << std::endl;
            throw std::logic_error("Stack is empty");
        }
        return m_data[topIndex];
    }

    ~Stack() {
        delete[] m_data;
    }
};

int main() {

    try {
        Stack<int> stack(1);

        stack.push(10);
        stack.push(20);
        stack.push(30);

        std::cout << "Stack size: " << stack.size() << std::endl;
        std::cout << "Top item: " << stack.top() << std::endl;

        stack.pop();

        std::cout << "Stack size: " << stack.size() << std::endl;
        std::cout << "Top item: " << stack.top() << std::endl;
    }

    catch (std::overflow_error & err) {
        std::cout << err.what() << std::endl;
    }
    catch (std::bad_alloc & err) {
        std::cout << err.what() << std::endl;
    }


}