#include <iostream>
#include <SFML/Graphics.hpp>
#include <AnimatedText.hpp>
#include <SFML/System/Sleep.hpp>

void mySleep(int duration) {
    sf::sleep(sf::milliseconds(duration));
}
int main()
{
    
    sf::RenderWindow window(sf::VideoMode(300, 300), "SFML works!");
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        std::cout << "font error";
        return 0;
    }
    text.setFont(font);
    text.setCharacterSize(24); // in pixels, not points!
    // set the color
    text.setFillColor(sf::Color::White);

     AnimatedText thing{};
     thing.setText("awdw");
     thing.setDuration(1);
    while (window.isOpen())
    {
        text.setString(thing.printAnimation()); // argument: calback : sleep fun 
     
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}
