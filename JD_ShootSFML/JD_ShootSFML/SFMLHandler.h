#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <optional>

struct RenderedSprite {
    sf::Texture texture;
    sf::Sprite sprite;
};
class SFMLHandler {
public:
    SFMLHandler(unsigned int width, unsigned int height, const std::string& title);

    void processEvents();
    void clear();                  
    void display();                
    bool isOpen() const;        
    sf::RenderWindow& getWindow();
    float getDeltaTime();             
   static sf::Sprite RenderSprite(sf::Texture& Texture, float X, float Y);
   static sf::Texture& GetTexture(const std::string& Path);
private:
    sf::RenderWindow window;
    sf::Clock clock;
    float deltaTime;

};
