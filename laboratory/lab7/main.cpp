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
public:
    Color m_color;
    std::vector<Vertex> m_crd{};
    double m_square;
    Figure(std::initializer_list<double> list) {
        std::vector<double> tmp_crd{};
        for (double x: list)
            tmp_crd.push_back(x);
        for (size_t i = 0; i < tmp_crd.size() / 2 + 2; i++) {
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
        std::sort(m_crd.begin(),m_crd.end(), sort_by_angle);
    }

    static bool sort_by_angle(Vertex arg1, Vertex arg2) {
        Vertex
                vector1 = {arg1.x - source_vertex.x, arg1.y - source_vertex.y},
                vector2 = {arg2.x - source_vertex.x, arg2.y - source_vertex.y},
                vector_OX = {0.0, 100.0};
        // find cos
        float cos1 = (vector1.x * vector_OX.x + vector1.y * vector_OX.y) /
                     ((pow(vector1.x * vector1.x + vector1.y * vector1.y, 0.5)) *
                      (pow(vector_OX.x * vector_OX.x + vector_OX.y * vector_OX.y, 0.5)));
        float cos2 = (vector_OX.x * vector2.x + vector_OX.y * vector2.y) /
                     ((pow(vector_OX.x * vector_OX.x + vector_OX.y * vector_OX.y, 0.5)) *
                      (pow(vector2.x * vector2.x + vector2.y * vector2.y, 0.5)));

        if (acos(cos1) > acos(cos2)) {
            return true;
        }
        if (cos1 == cos2) {
            return false;
        }
    }

    void print() {
        std::cout << m_crd.size() << std::endl;
        for (size_t i{}; i < m_crd.size(); i++)
            std::cout << m_crd[i].x << " " << m_crd[i].y << std::endl;
    }

};

class Triangle : private Figure {
    // contained self methods
public:
    Triangle(std::initializer_list<double> list) : Figure(list) {};
};

int main() {
    Figure a({3.97, 0.82, 2.26, 3.69, 5.39, 2.16});
    a.print();
    return 0;
}