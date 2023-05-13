#include <iostream>
#include <stdexcept>

template <typename T>
class Stack {
private:
    T* m_data;
    int capacity;
    int topIndex;

public:
    Stack(int size) : capacity(size), topIndex(0) {
        try {
            m_data = new T[capacity];
        } catch (const std::bad_alloc& e) {
            std::cout << "Failed memory allocation" << std::endl;
            throw;
        }
    }

    int size() const {
        return topIndex;
    }

    bool empty() const {
        return !topIndex;
    }

    void push(const T& item) {
        if (topIndex == capacity - 1) {
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
        bool a  = empty();
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
    Stack<int> stack(5);

    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Stack size: " << stack.size() << std::endl;
    std::cout << "Top item: " << stack.top() << std::endl;

    stack.pop();

    std::cout << "Stack size: " << stack.size() << std::endl;
    std::cout << "Top item: " << stack.top() << std::endl;


}