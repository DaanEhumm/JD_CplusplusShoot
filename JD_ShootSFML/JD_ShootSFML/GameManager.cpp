#include "GameManager.h"
#include <algorithm> 
#include "Enemey.h"
#include "SFMLHandler.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Player.h"

GameManager::GameManager()
     {
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

        player.update(deltaTime, SFMLHandler::GetWindow(), bullets);

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
                    enemy.takeDamage(35.f); 
                }
            }
        }

		// Remove bullets that are off-screen or have hit an enemy
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
            [&window = SFMLHandler::GetWindow()](const Bullet& b) {
                return b.isOffScreen(window) || b.hit;
            }),
            bullets.end());
		// Remove dead enemies 
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [](const Enemy& e) { return !e.isAlive(); }),
            enemies.end());


        SFMLHandler::Clear();
        player.draw(SFMLHandler::GetWindow());

        for (auto& enemy : enemies)
            SFMLHandler::GetWindow().draw(enemy.Sprite);

        for (auto& bullet : bullets)
            bullet.draw(SFMLHandler::GetWindow());

        SFMLHandler::Display();
    }
}