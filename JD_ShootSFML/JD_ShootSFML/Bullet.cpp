#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f velocity)
    : velocity(velocity) {
    shape.setRadius(5.f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(pos);
}

void Bullet::update(float deltaTime) {
    shape.move(velocity * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

bool Bullet::isOffScreen(const sf::RenderWindow& window) const {
    sf::Vector2f pos = shape.getPosition();
    return pos.x < 0 || pos.x > window.getSize().x || pos.y < 0 || pos.y > window.getSize().y;
}