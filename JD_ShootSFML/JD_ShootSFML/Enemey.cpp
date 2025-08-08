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
Enemy::Enemy()
    : Sprite(SFMLHandler::GetTexture("assets/textures/enemyAttack1.png")), Health(100.f), Speed(100.f), DealtDamage(false) // verrander texture naar jou texture
{
    Sprite.setPosition(sf::Vector2f(800, 400)); //  spawn voor nu 
    Sprite.setScale(sf::Vector2(1.2f, 1.2f));
}

void Enemy::Move(const sf::Vector2f& targetPosition)
{
    sf::Vector2f currentPos = Sprite.getPosition();
    sf::Vector2f direction = targetPosition - currentPos;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y); // heel simpel A^2 + B^2 = C^2, om de afstand te berekenen.

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

