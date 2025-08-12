#include "GameManager.h"
#include <algorithm> 
#include "Enemey.h"
#include "SFMLHandler.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
bool  GameManager::goingUp = false;
float GameManager::floorY = 555.f;
float GameManager::jumpApex = 450.f;
float GameManager::jumpSpeed = 300.f;
GameManager::GameManager()
    : skySprite(SFMLHandler::GetTexture("assets/textures/sky.png")),
    roadSprite(SFMLHandler::GetTexture("assets/textures/road.png"))
  
{
    skySprite.setScale({ 10.43f, 0.5f });
	roadSprite.setScale({ 10.43f, 0.4f });
    skySprite.setPosition(sf::Vector2f(0.f, 0.f));
    roadSprite.setPosition(sf::Vector2f( 0.f, 172.f )); 
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

        // in GameManager::run()
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

        skySprite.setPosition(sf::Vector2(-worldOffsetX * 0.5f, 0.f)); 
        roadSprite.setPosition(sf::Vector2(-worldOffsetX, 172.f));

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

        SFMLHandler::Display();
    }
}