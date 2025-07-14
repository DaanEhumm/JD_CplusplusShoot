#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"

class GunBase {
public:
    virtual void shoot(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets) = 0;
    virtual void update(float deltaTime) = 0;
    virtual ~GunBase() = default;
};