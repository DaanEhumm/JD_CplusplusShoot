#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(sf::Vector2f pos, sf::Vector2f velocity, const sf::Texture& texture);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isOffScreen(const sf::RenderWindow& window) const;

private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
};