#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
struct Vertex {
    double x{}, y{};

    Vertex() = default;

    Vertex(double tx, double ty) : x(tx), y(ty) {};

    void setCrd(double tx, double ty) {
        x = tx;
        y = ty;
    }
};

class KinematicSolver {
    double L1;
    double L2;
    Vertex M1;
    Vertex M2;
public:
    KinematicSolver(double tL1, double tL2, double tx, double ty) : L1(tL1), L2(tL2), M2(tx, ty) {
        try{
            if ((L1+L2)<(pow(M2.x * M2.x + M2.y * M2.y, 0.5))){
                throw std::exception();
            }
            if ((pow(M2.x * M2.x + M2.y * M2.y, 0.5)+L2)<(L1)){
                throw std::exception();
            }
            if ((L1+pow(M2.x * M2.x + M2.y * M2.y, 0.5))<(L2)){
                throw std::exception();
            }
        }
        catch(const std::exception& err) {
            std::cout << "Incorrect value" << std::endl;
            exit(0);
        }
    };

    std::vector<double> getAngle() {
        double angleA;
        double angleB;
        double angleC;
        angleA = 1 / cos(((M2.x * M2.x + M2.y * M2.y) + L2 - L1) / (2 * L2 * pow(M2.x * M2.x + M2.y * M2.y, 0.5)));
        angleB = 1 / cos((-(M2.x * M2.x + M2.y * M2.y) + L2 + L1) / (2 * L2 * L1));
        // 90 triangle
        angleC = acos(pow(M2.y * M2.y, 0.5)/pow(M2.x * M2.x + M2.y * M2.y, 0.5));
        return std::vector<double>{angleA, angleB, angleC};
    }

    Vertex getL1EndCor(){
        const double PI = 3.14159265358979323846;
        double alpha = (180 - getAngle()[0]* 180.f / PI - (180 - abs(getAngle()[1]*180.f / PI))) + getAngle()[2]* 180.f / PI;
        double beta = 180 - abs(getAngle()[1]*180.f / PI);
        double oppSide = 10.0*sin(alpha*3.14159/180);
        double adjSide = 10.0*cos(alpha*3.14159/180);
        std::cout << "alpha "<< alpha << std::endl;
        std::cout << "beta "<< beta << std::endl;
        std::cout << "coord L1 "<< oppSide<< " " << adjSide << std::endl;
        return Vertex(oppSide,adjSide);
    }

    Vertex getSourceCord(){
        return M2;
    }
};

int main() {
    KinematicSolver a(11.0,20.0,20.0,20.0);
    Vertex res = a.getL1EndCor();
        sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
        window.setFramerateLimit(60);

        sf::VertexArray points(sf::Points, 3);
        points[0].position = sf::Vector2f(400, 300);
        points[1].position = sf::Vector2f(400 + 10*res.x, 300-10*res.y);
        points[2].position = sf::Vector2f(400 + 10*a.getSourceCord().x, 300- 10*a.getSourceCord().y);

        float pointRadius = 10.f;

        sf::VertexArray lines(sf::LinesStrip, points.getVertexCount());

        sf::VertexArray axis(sf::Lines, 4);
        axis[0].position = sf::Vector2f(0.f, 300.f);
        axis[1].position = sf::Vector2f(800.f, 300.f);
        axis[2].position = sf::Vector2f(400.f, 0.f);
        axis[3].position = sf::Vector2f(400.f, 600.f);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();

            // Отрисовка координатных осей
            window.draw(axis);

            // Отрисовка соединительных линий между точками
            for (size_t i = 0; i < points.getVertexCount(); ++i) {
                lines[i].position = points[i].position;
                lines[i].color = sf::Color::White;
            }
            window.draw(lines);

            // Отрисовка точек
            sf::CircleShape pointShape(pointRadius);
            pointShape.setFillColor(sf::Color::White);

            for (size_t i = 0; i < points.getVertexCount(); ++i) {
                pointShape.setPosition(points[i].position);
                window.draw(pointShape);
            }

            window.display();
        }

    return 0;
}
