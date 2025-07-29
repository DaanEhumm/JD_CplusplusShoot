#include "Pistol.h"
#include <iostream>
#include <cmath>

Pistol::Pistol() {
    if (!pistolTexture.loadFromFile("assets/textures/pistol.png")) {
        std::cerr << "Failed to load pistol texture" << std::endl;
    }
    else {
        std::cout << "Pistol texture loaded successfully" << std::endl;

        sprite.emplace(pistolTexture);
        sprite->setOrigin(sf::Vector2f(pistolTexture.getSize().x / 2.f, pistolTexture.getSize().y / 2.f));
        sprite->setScale(sf::Vector2f(1.f, 1.f));
    }

    if (!bulletTexture.loadFromFile("assets/textures/pistolBullet.png")) {
        std::cerr << "Failed to load pistol bullet texture" << std::endl;
    }
}

void Pistol::shoot(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets) {
    sf::Vector2f normalizedDir = direction;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0.f) normalizedDir /= length;

    sf::Vector2f offset = normalizedDir * (pistolTexture.getSize().x * sprite->getScale().x / 2.f);
    sf::Vector2f bulletStart = sprite->getPosition() + offset;

    bullets.emplace_back(bulletStart, normalizedDir * 500.f, bulletTexture);
}

void Pistol::update(float deltaTime) {
}

void Pistol::draw(sf::RenderWindow& window) {
    if (sprite) window.draw(*sprite);
}

void Pistol::setPosition(const sf::Vector2f& pos, sf::RenderWindow& window) {
    if (!sprite) return;

    sprite->setPosition(pos);

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldMouse = window.mapPixelToCoords(mousePos);
    sf::Vector2f aimDir = worldMouse - pos;

    float angleInRadians = std::atan2(aimDir.y, aimDir.x);
    sprite->setRotation(sf::degrees(angleInRadians * 180.f / 3.14159f));
}