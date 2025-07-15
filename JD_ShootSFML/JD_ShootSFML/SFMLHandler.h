#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <optional>

class SFMLHandler {
public:
    SFMLHandler(unsigned int width, unsigned int height, const std::string& title);

    void processEvents();
    void clear();                  
    void display();                
    bool isOpen() const;        
    sf::RenderWindow& getWindow();
    float getDeltaTime();             

private:
    sf::RenderWindow window;
    sf::Clock clock;
    float deltaTime;
};
