#pragma once
#include "SFMLHandler.h"
#include "Player.h"
#include "Bullet.h"
#include <vector>

class GameManager {
public:
    GameManager();
    void run();

private:
 
    Player player;
    std::vector<Bullet> bullets;
};
