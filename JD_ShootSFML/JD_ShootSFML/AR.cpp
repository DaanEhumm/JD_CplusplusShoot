#include "AR.h"  
#include <iostream>  
#include "SFML/Graphics.hpp"  
#include "SFML/System.hpp"  

AR::AR() : sprite(texture){
  if (!texture.loadFromFile("assets/textures/ar.png")) {  
      std::cerr << "Failed to load AR texture" << std::endl;  
  }    
  sprite.setScale(sf::Vector2f(0.1f, 0.1f));  
}  

void AR::shoot(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets) {  
  bullets.emplace_back(position, direction * 800.f);  
}  

void AR::update(float deltaTime) {  
}  

void AR::draw(sf::RenderWindow& window) {  
  window.draw(sprite);  
}  

void AR::setPosition(const sf::Vector2f& pos) {  
  sprite.setPosition(pos);  

  sf::Vector2i mousePos = sf::Mouse::getPosition();  
  sf::Vector2f aimDir = sf::Vector2f(mousePos) - pos;  

  float angleInDegrees = std::atan2(aimDir.y, aimDir.x) * 180 / 3.14159f;  
  sprite.setRotation(sf::degrees(angleInDegrees));  
}