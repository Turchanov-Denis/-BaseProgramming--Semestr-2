 #include <iostream>
#include <SFML/Graphics.hpp>
#include <AnimatedText.hpp>
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
    std::string str = "awd";
    text.setString(str);
    text.setCharacterSize(24); // in pixels, not points!
    // set the color
    text.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        str += "a";
        text.setString(str);
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
