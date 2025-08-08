/*#include "Pistol.h"
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

Pistol::Pistol() {
    if (!pistolTexture.loadFromFile("assets/textures/pistol.png")) {
        std::cerr << "Failed to load pistol texture!" << std::endl;
    }
    if (!bulletTexture.loadFromFile("assets/textures/pistolBullet.png")) {
        std::cerr << "Failed to load pistol bullet texture!" << std::endl;
    }

    sprite.emplace(pistolTexture);
    sprite->setOrigin(sf::Vector2f(pistolTexture.getSize().x / 2.f, pistolTexture.getSize().y / 2.f));
    sprite->setScale(sf::Vector2f(1.f, 1.f));

    magazineSize = currentAmmo = 12;
    reserveAmmo = 5;
    reloadTime = 1.f;
    fireCooldown = 0.3f;
}

void Pistol::spawnBullet(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets) {
    bullets.emplace_back(position + direction * 25.f, direction * 600.f, bulletTexture);
}

void Pistol::setPosition(const sf::Vector2f& pos, sf::RenderWindow& window) {
    if (!sprite) return;

    sf::Vector2f aim = window.mapPixelToCoords(sf::Mouse::getPosition(window)) - pos;
    float angle = std::atan2(aim.y, aim.x) * 180.f / 3.14159f;

    const float maxAngle = 10.f;
    if (angle > maxAngle) angle = maxAngle;
    else if (angle < -maxAngle) angle = -maxAngle;

    sf::Vector2f offset(24.f, -10.f);

    float rad = angle * 3.14159f / 180.f;
    sf::Vector2f rotatedOffset(
        offset.x * std::cos(rad) - offset.y * std::sin(rad),
        offset.x * std::sin(rad) + offset.y * std::cos(rad)
    );

    sprite->setPosition(pos + rotatedOffset);
    sprite->setScale(sf::Vector2(0.7f, 0.7f));
    sprite->setRotation(sf::degrees(angle));
}
*/