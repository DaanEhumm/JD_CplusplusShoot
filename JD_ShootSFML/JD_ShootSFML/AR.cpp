#include "AR.h"

void AR::shoot(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets) {
    bullets.emplace_back(position, direction * 800.f); 
}

void AR::update(float deltaTime) {

}