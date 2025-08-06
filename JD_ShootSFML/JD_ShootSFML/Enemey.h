#pragma once
#include <SFML/Graphics.hpp>
class Enemy
{
public: 
    Enemy();
    sf::Sprite Sprite; 
    void Move(const sf::Vector2f& targetPosition);
private: 
    float Health ;
    float Speed;
};

