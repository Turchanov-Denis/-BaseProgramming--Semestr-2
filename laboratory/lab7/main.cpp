#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

enum class Color {
    Red,
    White,
};
typedef struct Vertex {
    double x, y;

    Vertex() {};

    Vertex(double tx, double ty) : x(tx), y(ty) {};

    void setCrd(double tx, double ty) {
        x = tx;
        y = ty;
    }
} Vertex; // define structure

static Vertex source_vertex;

class Figure {
    // store
protected:
    Color m_color;
    std::vector<Vertex> m_crd{};

    Figure(std::initializer_list<double> list, Color color = Color::White) {
        m_color = color;
        std::vector<double> tmp_crd{};
        for (double x: list)
            tmp_crd.push_back(x);
        for (size_t i = 0; i <= tmp_crd.size() / 2 + 2; i++) {
            m_crd.push_back(Vertex(tmp_crd[i], tmp_crd[i + 1]));
            i++;
        }
        // find source
        for (size_t i{}; i < m_crd.size(); i++) {
            if (m_crd[i].x < m_crd[i + 1].x) {
                source_vertex.setCrd(m_crd[i].x, m_crd[i].y);
            }
        }
//        std::cout << source_vertex.x <<"-"<< source_vertex.y << std::endl;
        std::sort(m_crd.begin(), m_crd.end(), sort_by_angle);
    }


    static bool sort_by_angle(Vertex arg1, Vertex arg2) {
        //std::cout << source_vertex.x << " - - - "<< source_vertex.y << std::endl;
        Vertex
                vector1 = {arg1.x - source_vertex.x, arg1.y - source_vertex.y},
                vector2 = {arg2.x - source_vertex.x, arg2.y - source_vertex.y},
                vector_OX = {0.0, 100.0};
        // find cos
        double cos1 = (vector1.x * vector_OX.x + vector1.y * vector_OX.y) /
                      ((pow(vector1.x * vector1.x + vector1.y * vector1.y, 0.5)) *
                       (pow(vector_OX.x * vector_OX.x + vector_OX.y * vector_OX.y, 0.5)));
        double cos2 = (vector_OX.x * vector2.x + vector_OX.y * vector2.y) /
                      ((pow(vector_OX.x * vector_OX.x + vector_OX.y * vector_OX.y, 0.5)) *
                       (pow(vector2.x * vector2.x + vector2.y * vector2.y, 0.5)));

        if (acos(cos1) > acos(cos2)) {
            return false;
        }
        return true;
    }

public:
    virtual double getSquare() {

        double res{};
        for (size_t i = 0; i < m_crd.size() - 1; i++) {
            //std::cout << i<< " - i - " << i+1 << std::endl;
            res += m_crd[i].x * m_crd[i + 1].y;
        }
        for (size_t j = m_crd.size() - 1; j >= 1; j--) {
            //std::cout << j<< " - j - " << j-1 << std::endl;
            res -= m_crd[j].x * m_crd[j - 1].y;
        }
        res += m_crd[m_crd.size() - 1].x * m_crd[0].y;
        res -= m_crd[0].x * m_crd[m_crd.size() - 1].y;
        return 0.5 * res;
    }

    void print() {
        std::cout << m_crd.size() << std::endl;
        for (size_t i{}; i < m_crd.size(); i++)
            std::cout << m_crd[i].x << " " << m_crd[i].y << std::endl;
    }

};

class Triangle : public Figure {
    // contained self methods
    size_t limit = 3;
public:
    Triangle(std::initializer_list<double> list, Color color) : Figure(list, color) {
        if (m_crd.size() != limit) {
            throw std::exception();
        }
    };
};

class Rectangle : public Figure {
    // contained self methods
    size_t limit = 4;
public:
    Rectangle(std::initializer_list<double> list, Color color) : Figure(list, color) {
        if (m_crd.size() != limit) {
            throw std::exception();
        }
    };
};

class Cycle : public Figure {
    // contained self methods
    size_t limit = 1;
    double m_radius;
public:
    Cycle(std::initializer_list<double> list, double radius) : Figure(list), m_radius(radius) {
        if (m_crd.size() != limit) {
            throw std::exception();
        }
    };

    double getSquare() override {
        return atan(1) * 4 * 2 * m_radius;
    }
};

enum class FigureType {
    TRIANGLE,
    RECTANGLE,
    CYCLE
};

Figure *factory(FigureType type,std::initializer_list<double> listCord,Color color = Color::White) {
    Figure* figure = nullptr;
    switch (type) {
        case FigureType::TRIANGLE:
            figure = new Triangle(listCord, color);
            break;
        case FigureType::RECTANGLE:
            figure = new Rectangle(listCord, color);
            break;
        case FigureType::CYCLE:
            double radius;
            std::cin>> radius;
            figure = new Cycle(listCord,radius);
            break;
    }
    return figure;
}

int main() {
    Figure* a = factory(FigureType::TRIANGLE,{3.97, 0.82, 2.26, 3.69, 5.39, 2.16});
    std::cout << a->getSquare() << std::endl;
    delete a;
    return 0;
}