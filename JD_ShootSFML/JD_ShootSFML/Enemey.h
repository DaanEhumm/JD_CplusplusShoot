#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
class Enemy
{
public: 
    Enemy();
    sf::Sprite Sprite; 
    void Move(const sf::Vector2f& targetPosition);
    void MoveToPlayer(Player& player);
    bool DealtDamage;
private: 
    void ResetCooldown();
    float Health ;
    float Speed;
};

