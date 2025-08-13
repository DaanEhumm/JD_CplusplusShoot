#include "GameManager.h"
#include <algorithm> 
#include "Enemey.h"
#include "SFMLHandler.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include <sstream>
#include <iomanip>
#include <iostream>

bool  GameManager::goingUp = false;
float GameManager::floorY = 555.f;
float GameManager::jumpApex = 450.f;
float GameManager::jumpSpeed = 300.f;

GameManager::GameManager()
    : skySprite(SFMLHandler::GetTexture("assets/textures/sky.png")),
    roadSprite(SFMLHandler::GetTexture("assets/textures/road.png")), 
	timerText(font), ammoText(font)
{
    skySprite.setScale({ 10.43f, 0.5f });
	roadSprite.setScale({ 10.43f, 0.4f });
    skySprite.setPosition(sf::Vector2f(0.f, 0.f));
    roadSprite.setPosition(sf::Vector2f( 0.f, 172.f )); 


	//HUD / UI setup
    if (!font.openFromFile("assets/fonts/Roboto-Regular.ttf")) {
        std::cout << "Failed to load HUD font\n";
    }  
    timerText.setFont(font);
    timerText.setCharacterSize(20);
    timerText.setString("00:00");
    timerText.setFillColor(sf::Color::White);
    timerText.setOutlineColor(sf::Color(0, 0, 0, 170));
    timerText.setOutlineThickness(2.f);

    ammoText.setFont(font);
    ammoText.setCharacterSize(20);
    ammoText.setFillColor(sf::Color::White);
    ammoText.setOutlineColor(sf::Color(0, 0, 0, 170));
    ammoText.setOutlineThickness(2.f);
    ammoText.setString("Ammo: 0 / 0");

    healthBarBackground.setSize({ 200.f, 20.f });  
    healthBarBackground.setFillColor(sf::Color(50, 50, 50, 200)); 
    healthBarBackground.setOrigin(healthBarBackground.getSize() * 0.5f);

    healthBar.setSize({ 200.f, 20.f });  // full health
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setOrigin(healthBar.getSize() * 0.5f);
}

bool intersects(const sf::FloatRect& a, const sf::FloatRect& b) {         // Help with bounds of enemy and bullet
    return a.position.x < b.position.x + b.size.x &&
        a.position.x + a.size.x > b.position.x &&
        a.position.y < b.position.y + b.size.y &&
        a.position.y + a.size.y > b.position.y;                  
}

void GameManager::run() {
    std::vector<Enemy> enemies;
    enemies.emplace_back(); // DIT IS TIJDELIJKK!!! 1 ENEMY TEST

    while (SFMLHandler::IsOpen()) {
        SFMLHandler::ProcessEvents();
        float deltaTime = SFMLHandler::GetDeltaTime();

        player.update(deltaTime, SFMLHandler::GetWindow(), bullets, worldOffsetX);

        if (player.wantsToMoveRightPastLimit) {
            float scrollSpeed = 200.f;
            worldOffsetX += scrollSpeed * deltaTime;
        }

        player.Jump();

        for (auto& bullet : bullets)
            bullet.update(deltaTime);

        for (auto& enemy : enemies)
            enemy.MoveToPlayer(player);

        for (auto& bullet : bullets) {
            for (auto& enemy : enemies) {
                sf::FloatRect bulletBounds = bullet.getBounds();
                sf::FloatRect enemyBounds = enemy.getBounds();

                if (!bullet.hit && intersects(bullet.getBounds(), enemy.getBounds())) {
                    bullet.hit = true;
                    enemy.takeDamage(40.f);
                }
            }
        }

        for (auto& enemy : enemies) {
            std::cout << enemy.state << std::endl;
            enemy.anim->CheckCondition(enemy.state);  // update animation (changes texture)
            enemy.anim2->CheckCondition(enemy.state);
            SFMLHandler::GetWindow().draw(enemy.Sprite);  // draw sprite with updated texture
        }

        // Remove bullets that are off-screen or have hit an enemy
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
            [this, &window = SFMLHandler::GetWindow()](const Bullet& b) {
                return b.isOffScreen(window, this->worldOffsetX) || b.hit;
            }),
            bullets.end());
        // Remove dead enemies 
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [](const Enemy& e) { return !e.isAlive(); }),
            enemies.end());


        SFMLHandler::Clear();

        skySprite.setPosition(sf::Vector2f(-worldOffsetX * 0.5f, 0.f));
        roadSprite.setPosition(sf::Vector2f(-worldOffsetX, 172.f));

        SFMLHandler::GetWindow().draw(skySprite);
        SFMLHandler::GetWindow().draw(roadSprite);

        sf::Vector2f playerPos = player.Sprite.getPosition();
        if (playerPos.x > 700.f) {
            player.Sprite.setPosition(sf::Vector2(700.f, playerPos.y));
        }
        player.draw(SFMLHandler::GetWindow());

        for (auto& enemy : enemies) {
            sf::Sprite& eSprite = enemy.Sprite;
            sf::Vector2f pos = eSprite.getPosition();
            eSprite.setPosition(sf::Vector2(pos.x - worldOffsetX, pos.y));
            SFMLHandler::GetWindow().draw(eSprite);
            eSprite.setPosition(pos);
        }

        for (auto& bullet : bullets) {
            sf::Vector2f screenPos = bullet.sprite.getPosition() - sf::Vector2f(worldOffsetX, 0.f);
            bullet.sprite.setPosition(screenPos);
            bullet.draw(SFMLHandler::GetWindow());
            bullet.sprite.setPosition(bullet.sprite.getPosition() + sf::Vector2f(worldOffsetX, 0.f));
        }

        // HUD / UI section
        // Timer
        // Get current view
        auto& window = SFMLHandler::GetWindow();
        sf::View view = window.getView();
        sf::Vector2f viewSize = view.getSize();
        sf::Vector2f viewCenter = view.getCenter();

        // Timer - bottom center
        const int total = static_cast<int>(timerClock.getElapsedTime().asSeconds());
        const int minutes = total / 60;
        const int seconds = total % 60;
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << minutes
            << ":" << std::setw(2) << std::setfill('0') << seconds;
        timerText.setString(oss.str());

        sf::FloatRect timerBounds = timerText.getLocalBounds();
        timerText.setOrigin(sf::Vector2f(timerBounds.position.x + timerBounds.size.x / 2.f,
            timerBounds.position.y + timerBounds.size.y / 2.f));
        timerText.setPosition(sf::Vector2f(viewCenter.x, viewCenter.y + viewSize.y / 2.f - 24.f));
        window.draw(timerText);

        // Ammo - bottom right
        GunBase* gun = player.getCurrentWeapon();
        oss.str(""); oss.clear();
        oss << gun->getCurrentAmmo() << " / " << gun->getReserveAmmo();
        ammoText.setString(oss.str());

        sf::FloatRect ammoBounds = ammoText.getLocalBounds();
        ammoText.setOrigin(sf::Vector2f(ammoBounds.position.x + ammoBounds.size.x,
            ammoBounds.position.y + ammoBounds.size.y));
        ammoText.setPosition(sf::Vector2f(viewCenter.x + viewSize.x / 2.f - 10.f,
            viewCenter.y + viewSize.y / 2.f - 10.f));
        window.draw(ammoText);

		// Health bar - top center 
        healthBarBackground.setPosition(sf::Vector2f(viewCenter.x, viewCenter.y - viewSize.y / 2.f + 20.f));
        healthBar.setPosition(sf::Vector2f(viewCenter.x, viewCenter.y - viewSize.y / 2.f + 20.f));

        // Update health value
        float healthPercent = static_cast<float>(player.getHealth()) / player.getMaxHealth();
        healthBar.setSize({ 200.f * healthPercent, 20.f });  // scale width by health %
        healthBar.setOrigin({ healthBar.getSize().x / 2.f, healthBar.getSize().y / 2.f });

        // Draw health bar
        window.draw(healthBarBackground);
        window.draw(healthBar);

        window.display();
    }
}