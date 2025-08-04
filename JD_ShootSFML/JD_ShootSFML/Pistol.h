#pragma once
#include "GunBase.h"
#include <SFML/Graphics.hpp>
#include <optional>

class Pistol : public GunBase {
public:
    Pistol();
    void setPosition(const sf::Vector2f& pos, sf::RenderWindow& window) override;

protected:
    void spawnBullet(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets) override;

private:
    sf::Texture pistolTexture;
};