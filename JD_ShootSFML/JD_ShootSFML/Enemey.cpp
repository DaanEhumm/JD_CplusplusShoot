#include "Enemey.h"
#include "SFMlHandler.h"
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>   // for sf::Window, events, input
#include "Player.h"
#include <thread>
#include <chrono>
#include <functional>
#include <cstdlib>
#include <ctime>

//const std::vector<std::string>& files, float interval, sf::Sprite& sprite
// In Enemy.cpp
Enemy::Enemy()
    : Sprite(SFMLHandler::GetTexture("assets/textures/enemyAttack1.png")),
    Health(100.f),
    Speed(100.f),
    DealtDamage(false), 
    state(CharacterState::Idle),
    anim(nullptr), // initialize pointer to null first
    anim2(nullptr)
{
    Sprite.setPosition(sf::Vector2f(800, 400));
    Sprite.setScale(sf::Vector2f(1.2f, 1.2f));

    // now Sprite is fully constructed, create Animation
    anim = new Animation(Animation::EnemyFiles, 0.2f, Sprite, CharacterState::Moving);
    anim2 = new Animation(Animation::AttackFiles, 0.2f, Sprite, CharacterState::Attacking);
}


void Enemy::Move(const sf::Vector2f& targetPosition)
{
    sf::Vector2f currentPos = Sprite.getPosition();
    sf::Vector2f direction = targetPosition - currentPos;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y); // heel simpel A^2 + B^2 = C^2, om de afstand te berekenen.
    if (state != CharacterState::Attacking) {
        state = CharacterState::Moving;
     }
    if (distance > 0.1f)
    {
        sf::Vector2f directionNorm = direction / distance;

        
        float deltaTime = 1.f / 60.f; // 60 = aantal frames, mag ook hoger kost wel meer kracht tho.

        sf::Vector2f movement = directionNorm * Speed * deltaTime;

        if ((movement.x * movement.x + movement.y * movement.y) > (distance * distance))
            Sprite.setPosition(targetPosition);
        else
            Sprite.move(movement);
    }
}
void Enemy::ResetCooldown() {
    std::thread([this]() {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        DealtDamage = false;
        state = CharacterState::Moving;
        }).detach();
}

void Enemy::ResetState() {
    std::thread([this]() {
        auto milliseconds = static_cast<int>((Enemy::anim2->interval * Enemy::anim2->files.size()) * 1000);
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

   
        state = CharacterState::Moving;
        }).detach();
}

void Enemy::MoveToPlayer(Player& player) {
    sf::Vector2f enemyPos = Sprite.getPosition();
    sf::Vector2f playerPos = player.Sprite.getPosition();


    float dx = playerPos.x - enemyPos.x;
    float dy = playerPos.y - enemyPos.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    Move(playerPos);
    if (distance < 20) {

        if (SFMLHandler::GetCollision(player.Sprite, Sprite) && DealtDamage == false) {
            state = CharacterState::Attacking;
            ResetState();
            player.TakeDamage(5);
            DealtDamage = true;
        
            std::cout << "player should have taken damage, new player health:" << player.Health << std::endl;
          
            ResetCooldown();
       }
    }


}
bool Enemy::isAlive() const {
    return Health > 0.f;
}

void Enemy::takeDamage(float damage) {
    Health -= damage;
    if (Health < 0.f) Health = 0.f;
}

sf::FloatRect Enemy::getBounds() const {
    return Sprite.getGlobalBounds();
}

