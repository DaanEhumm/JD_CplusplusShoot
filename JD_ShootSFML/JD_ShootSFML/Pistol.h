#pragma once
#include "GunBase.h"
#include <SFML/Graphics.hpp>
#include <optional>

class Pistol : public GunBase {
public:
    Pistol();
    void shoot(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void setPosition(const sf::Vector2f& pos, sf::RenderWindow& window) override;

private:
    sf::Texture pistolTexture;
    std::optional<sf::Sprite> sprite;
    
    sf::Texture bulletTexture;
    
};