#include "AR.h"  
#include <iostream>  
#include <cmath>  
#include <SFML/System.hpp>  
#include <SFML/Graphics.hpp>  

AR::AR() {  
   if (!gunTexture.loadFromFile("assets/textures/ar.png")) {  
       std::cerr << "Failed to load AR texture!" << std::endl;  
   }  
   if (!bulletTexture.loadFromFile("assets/textures/arBullet.png")) {  
       std::cerr << "Failed to load AR bullet texture!" << std::endl;  
   }  

   sprite.emplace(gunTexture);  
   sprite->setOrigin(sf::Vector2f(gunTexture.getSize().x / 2.f, gunTexture.getSize().y / 2.f));  
   sprite->setScale(sf::Vector2f(0.8f, 0.8f));  

   magazineSize = currentAmmo = 30;  
   reserveAmmo = 590;  
   reloadTime = 1.5f;  
   fireCooldown = 0.1f;  
}  

void AR::spawnBullet(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets) {  
   bullets.emplace_back(position + direction * 25.f, direction * 800.f, bulletTexture);  

   
}  

void AR::setPosition(const sf::Vector2f& pos, sf::RenderWindow& window) {  
    if (!sprite) return;

    sf::Vector2f aim = window.mapPixelToCoords(sf::Mouse::getPosition(window)) - pos;
    float angle = std::atan2(aim.y, aim.x) * 180.f / 3.14159f;

    const float maxAngle = 10.f;
    if (angle > maxAngle) angle = maxAngle;
    else if (angle < -maxAngle) angle = -maxAngle;

    sf::Vector2f offset(20.f, -2.f);

    float rad = angle * 3.14159f / 180.f;
    sf::Vector2f rotatedOffset(
        offset.x * std::cos(rad) - offset.y * std::sin(rad),
        offset.x * std::sin(rad) + offset.y * std::cos(rad)
    );

    sprite->setPosition(pos + rotatedOffset);;
    sprite->setScale(sf::Vector2(1.f, 1.f));
    sprite->setRotation(sf::degrees(angle));
}
