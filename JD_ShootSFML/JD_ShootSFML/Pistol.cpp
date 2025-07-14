#include "Pistol.h"

void Pistol::shoot(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets) {
    bullets.emplace_back(position, direction * 500.f); 
}

void Pistol::update(float deltaTime) {
}