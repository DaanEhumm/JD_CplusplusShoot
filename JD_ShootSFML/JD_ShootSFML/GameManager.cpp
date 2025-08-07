#include "GameManager.h"
#include <algorithm> 
#include "Enemey.h"
GameManager::GameManager()
     {
}




void GameManager::run() {
    Enemy enemy = Enemy();
    while (SFMLHandler::IsOpen()) {
        SFMLHandler::ProcessEvents();

        float deltaTime = SFMLHandler::GetDeltaTime();

        player.update(deltaTime, SFMLHandler::GetWindow(), bullets);

        for (auto& bullet : bullets)
            bullet.update(deltaTime);

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
            [&window = SFMLHandler::GetWindow()](Bullet& b) {
                return b.isOffScreen(window);
            }),
            bullets.end());

        SFMLHandler::Clear();
        player.draw(SFMLHandler::GetWindow());

        SFMLHandler::GetWindow().draw(enemy.Sprite);
        enemy.MoveToPlayer(player);
        for (auto& bullet : bullets)
            bullet.draw(SFMLHandler::GetWindow());

        SFMLHandler::Display();
    }
}