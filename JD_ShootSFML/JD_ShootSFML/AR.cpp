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

   magazineSize = currentAmmo = 26;  
   reserveAmmo = 260;  
   reloadTime = 1.5f;  
   fireCooldown = 0.1f;  
}  

void AR::spawnBullet(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets, float worldOffsetX) {  
   bullets.emplace_back(position + direction * 25.f, direction * 800.f, bulletTexture);  
   (position - sf::Vector2f(worldOffsetX, 0.f)) + direction * 25.f, // screen position
       direction * 800.f,
       bulletTexture;
}  

void AR::setPosition(const sf::Vector2f& pos, sf::RenderWindow& window) {
    if (!sprite) return;

    sf::Vector2f offset(11.f, -49.f);
    sprite->setPosition(pos + offset);;
    sprite->setScale(sf::Vector2(0.9f, 0.9f));
    sprite->setRotation(sf::degrees(0.f));

}
