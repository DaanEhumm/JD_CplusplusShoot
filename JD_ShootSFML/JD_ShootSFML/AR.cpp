#include "AR.h"  
#include <iostream>  
#include <cmath>
#include "SFML/Graphics.hpp"  
#include "SFML/System.hpp"  

AR::AR() {
    if (!texture.loadFromFile("assets/textures/ar.png")) {
        std::cerr << "Failed to load AR texture" << std::endl;
    }
    else {
        std::cout << "AR texture loaded successfully" << std::endl;

        sprite.emplace(texture);
        sprite->setOrigin(sf::Vector2f(texture.getSize().x / 2.3f, texture.getSize().y / 4.5f));
        sprite->setScale(sf::Vector2f(1.f, 1.f));
        sprite->setColor(sf::Color::White);

        std::cout << "Texture size: " << texture.getSize().x << "x" << texture.getSize().y << std::endl;
    }

    if (!bulletTexture.loadFromFile("assets/textures/arBullet.png")) {
        std::cerr << "Failed to load bullet texture" << std::endl;
    }
}

void AR::shoot(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets) {
    if (!sprite) return;

    float bulletOffsetDistance = 25.f; 
    sf::Vector2f offset = direction * bulletOffsetDistance;
    sf::Vector2f bulletStart = sprite->getPosition() + offset;

    bullets.emplace_back(bulletStart, direction * 800.f, bulletTexture);
}

void AR::update(float deltaTime) {  
}  

void AR::draw(sf::RenderWindow& window) {
    if (sprite) window.draw(*sprite);
}   

void AR::setPosition(const sf::Vector2f& pos, sf::RenderWindow& window) {  
    if (!sprite) return;

    sprite->setPosition(pos);

 sf::Vector2i mousePos = sf::Mouse::getPosition(window);  
 sf::Vector2f worldMouse = window.mapPixelToCoords(mousePos);  
 sf::Vector2f aimDir = worldMouse - pos;  

 float angleInRadians = std::atan2(aimDir.y, aimDir.x);
 sprite->setRotation(sf::degrees(angleInRadians * 180.f / 3.14159f));
}