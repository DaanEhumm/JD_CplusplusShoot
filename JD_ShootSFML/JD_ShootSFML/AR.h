#pragma once
#include "GunBase.h"

class AR : public GunBase {
public:
    void shoot(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets) override;
    void update(float deltaTime) override;
};

