#pragma once
#include "SFMLHandler.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemey.h"
#include <vector>
#include <SFML/Graphics.hpp>

class GameManager {
public:
    GameManager();
    void run();

  static  bool goingUp ;
  static float floorY;
  static float jumpApex;
  static float jumpSpeed ;
    sf::Vector2f getPlayerWorldPosition() const {
        return player.Sprite.getPosition() + sf::Vector2f(worldOffsetX, 0.f);
    }
    float worldOffsetX = 0.f;
private:
 
    Player player;
    std::vector<Bullet> bullets;

    sf::Sprite skySprite;
    sf::Sprite roadSprite;
    
    sf::Font font;
    sf::Text timerText;
    sf::Clock timerClock;

    sf::Text ammoText;

    sf::RectangleShape healthBarBackground;
    sf::RectangleShape healthBar;
};
