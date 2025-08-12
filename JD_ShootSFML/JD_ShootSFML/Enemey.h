#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"
#include "CharacterStates.h"
class Enemy
{
public: 
    Enemy();
    sf::Sprite Sprite; 
    void Move(const sf::Vector2f& targetPosition);
    void MoveToPlayer(Player& player);
    bool DealtDamage;
    CharacterState state;
    bool isAlive() const;
    void takeDamage(float damage);
    sf::FloatRect getBounds() const;
    Animation* anim;
    ~Enemy() {
        delete anim;
        delete anim2;
    }

    Animation* anim2;  // if more animations are nesisary, do a different approach but for now we only need 2 so this is fine.

private: 
    void ResetCooldown();
    void ResetState();
    float Health ;
    float Speed;

};

