#pragma once
#include "GunBase.h"
#include <optional>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class AR : public GunBase {
public:
    AR();
    void setPosition(const sf::Vector2f& pos, sf::RenderWindow& window) override;

protected:
    void spawnBullet(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets) override;

private:
    sf::Texture gunTexture;
};
