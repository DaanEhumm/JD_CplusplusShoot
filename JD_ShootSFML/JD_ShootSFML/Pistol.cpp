#include "Pistol.h"
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
   float rotation = std::atan2(aim.y, aim.x) * 180.f / 3.14159f;
   sprite->setPosition(pos);
   sprite->setRotation(sf::degrees(rotation));
}