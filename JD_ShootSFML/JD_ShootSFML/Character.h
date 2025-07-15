#pragma once
#include <SFML/Graphics.hpp>
#include "GunBase.h"
#include <vector>
#include "Bullet.h"

class Character {
public:
    virtual void update(float deltaTime, sf::RenderWindow& window, std::vector<Bullet>& bullets) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~Character() = default;

protected:
    sf::RectangleShape body;
    GunBase* gun = nullptr;
};
