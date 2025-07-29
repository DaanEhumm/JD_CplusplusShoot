#include "GameManager.h"
#include <algorithm> 

GameManager::GameManager()
    : sfml(800, 600, "Shooter 1v1") {
}

void GameManager::run() {
    while (sfml.isOpen()) {
        sfml.processEvents();
        float deltaTime = sfml.getDeltaTime();

        player.update(deltaTime, sfml.getWindow(), bullets);

        for (auto& bullet : bullets)
            bullet.update(deltaTime);

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
            [&window = sfml.getWindow()](Bullet& b) {
                return b.isOffScreen(window);
            }),
            bullets.end());

        sfml.clear();
        player.draw(sfml.getWindow());

        for (auto& bullet : bullets)
            bullet.draw(sfml.getWindow());

        sfml.display();
    }
}