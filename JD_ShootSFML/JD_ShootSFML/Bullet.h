#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(sf::Vector2f pos, sf::Vector2f velocity, const sf::Texture& texture);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isOffScreen(const sf::RenderWindow& window, float worldOffsetX) const;

    bool hit = false;
    sf::FloatRect getBounds() const;
    sf::Sprite sprite;
private:
    sf::Vector2f velocity;
    sf::Vector2f worldPos;
}; 