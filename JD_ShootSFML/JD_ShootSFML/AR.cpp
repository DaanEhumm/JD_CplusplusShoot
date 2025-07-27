#include "AR.h"  
#include <iostream>  
#include "SFML/Graphics.hpp"  
#include "SFML/System.hpp"  

AR::AR() : sprite(texture) {
    if (!texture.loadFromFile("assets/textures/ar.png")) {
        std::cerr << "Failed to load AR texture" << std::endl;
    }
    else {
        std::cout << "AR texture loaded successfully" << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.f, texture.getSize().y / 2.f));
    sprite.setScale(sf::Vector2f(1.f, 1.f));
    sprite.setColor(sf::Color::White);

    std::cout << "Texture size: " << texture.getSize().x << "x" << texture.getSize().y << std::endl;

}

void AR::shoot(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets) {  
  bullets.emplace_back(position, direction * 800.f);  
}  

void AR::update(float deltaTime) {  
}  

void AR::draw(sf::RenderWindow& window) {
    std::cout << "Drawing AR at: "
        << sprite.getPosition().x << ", "
        << sprite.getPosition().y << std::endl;

  window.draw(sprite);  
}   

void AR::setPosition(const sf::Vector2f& pos, sf::RenderWindow& window) {  
 sprite.setPosition(pos);  

 sf::Vector2i mousePos = sf::Mouse::getPosition(window);  
 sf::Vector2f worldMouse = window.mapPixelToCoords(mousePos);  
 sf::Vector2f aimDir = worldMouse - pos;  

 float angleInDegrees = std::atan2(aimDir.y, aimDir.x) * 180 / 3.14159f;  
 sprite.setRotation(sf::degrees(angleInDegrees));
}