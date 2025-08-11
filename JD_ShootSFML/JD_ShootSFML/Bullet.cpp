#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f velocity, const sf::Texture& texture)
    : velocity(velocity), sprite(texture), hit(false), worldPos(pos) {

    sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));

	sf::Vector2f bulletOffset(11.f, -63.f);                                    
    float angle = std::atan2(velocity.y, velocity.x) * 180.f / 3.14159f;
    float rad = angle * 3.14159f / 180.f;
     
    sf::Vector2f rotatedOffset(
        bulletOffset.x * std::cos(rad) - bulletOffset.y * std::sin(rad),
        bulletOffset.x * std::sin(rad) + bulletOffset.y * std::cos(rad)
    );

    worldPos += rotatedOffset;
    sprite.setPosition(worldPos);
    sprite.setRotation(sf::degrees(angle));
    sprite.setScale(sf::Vector2f(1.0f, 1.0f));  
}

void Bullet::update(float deltaTime) {
    worldPos += velocity * deltaTime;
    sprite.move(velocity * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Bullet::isOffScreen(const sf::RenderWindow& window, float worldOffsetX) const {
    sf::Vector2f worldPos = sprite.getPosition();
    worldPos.x += worldOffsetX;

    const float WORLD_LEFT = 0.f;
    const float WORLD_RIGHT = 5000.f; 
    const float WORLD_TOP = 0.f;
    const float WORLD_BOTTOM = 600.f;

    return (worldPos.x < WORLD_LEFT || worldPos.x > WORLD_RIGHT ||
        worldPos.y < WORLD_TOP || worldPos.y > WORLD_BOTTOM);
}

sf::FloatRect Bullet::getBounds() const {
    return sprite.getGlobalBounds();
}