#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f velocity, const sf::Texture& texture)
    : velocity(velocity), sprite(texture), hit(false) {

    sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));

	sf::Vector2f bulletOffset(12.f, -15.f); 
    float angle = std::atan2(velocity.y, velocity.x) * 180.f / 3.14159f;
    float rad = angle * 3.14159f / 180.f;

    sf::Vector2f rotatedOffset(
        bulletOffset.x * std::cos(rad) - bulletOffset.y * std::sin(rad),
        bulletOffset.x * std::sin(rad) + bulletOffset.y * std::cos(rad)
    );

    sprite.setPosition(pos + rotatedOffset);
    sprite.setRotation(sf::degrees(angle));
    sprite.setScale(sf::Vector2f(1.0f, 1.0f));  
}

void Bullet::update(float deltaTime) {
    sprite.move(velocity * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Bullet::isOffScreen(const sf::RenderWindow& window) const {
    sf::Vector2f pos = sprite.getPosition();
    return pos.x < 0 || pos.x > window.getSize().x || pos.y < 0 || pos.y > window.getSize().y;
}

sf::FloatRect Bullet::getBounds() const {
    return sprite.getGlobalBounds();
}