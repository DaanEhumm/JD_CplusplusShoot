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
    : Sprite(SFMLHandler::GetTexture("assets/textures/enemyAttack1.png")), Health(100.f), Speed(100.f), DealtDamage(false)
{
    const sf::FloatRect bounds = Sprite.getLocalBounds();
    Sprite.setOrigin({ bounds.position.x + bounds.size.x * 0.5f, bounds.position.y + bounds.size.y });

    Sprite.setScale({ 1.2f, 1.2f });


    constexpr float GROUND_Y = 555.f;
    Sprite.setPosition({ 800.f, GROUND_Y });
}

void Enemy::Move(const sf::Vector2f& targetPosition)
{
    constexpr float GROUND_Y = 555.f;

    sf::Vector2f currentPos = Sprite.getPosition();
    sf::Vector2f target = targetPosition;
    target.y = GROUND_Y;

    sf::Vector2f direction = target - currentPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y); // heel simpel A^2 + B^2 = C^2, om de afstand te berekenen.

    if (distance > 0.01f)
    {
        sf::Vector2f dirNorm = direction / distance;
        float deltaTime = SFMLHandler::GetDeltaTime(); // smooth timing
        sf::Vector2f movement = dirNorm * Speed * deltaTime;

        float moveSq = (movement.x * movement.x + movement.y * movement.y);
        float distSq = (distance * distance);

        if (moveSq >= distSq)
            Sprite.setPosition(target);
        else
            Sprite.move(movement);
    }

    sf::Vector2f pos = Sprite.getPosition();
    if (pos.y > GROUND_Y) pos.y = GROUND_Y;
    Sprite.setPosition(pos);
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

