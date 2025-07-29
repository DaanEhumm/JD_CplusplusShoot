#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f velocity, const sf::Texture& texture)
    : velocity(velocity), sprite(texture) {

    sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
    sprite.setPosition(pos);

    float angle = std::atan2(velocity.y, velocity.x) * 180.f / 3.14159f;

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