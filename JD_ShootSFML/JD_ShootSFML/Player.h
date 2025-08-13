#pragma once
#include "Character.h"
#include "AR.h"
#include "Pistol.h"
#include <SFML/Graphics.hpp>
class Player : public Character {
public:
    Player();
    void update(float deltaTime, sf::RenderWindow& window, std::vector<Bullet>& bullets, float worldOffsetX) override;
    void draw(sf::RenderWindow& window) override;
    sf::Sprite Sprite;
    int Health;
    void TakeDamage(int Damage);
    bool wantsToMoveRightPastLimit = false;
    void Jump();
  
    bool isjumping;

    GunBase* getCurrentWeapon() {
        return weapons[currentWeaponIndex].get();
    }

    int getHealth() const { return Health; }
    int getMaxHealth() const { return 100; }

private:
    void AddForce();
    std::vector<std::unique_ptr<GunBase>> weapons;
    void ResetJump();
    int currentWeaponIndex = 0;
    bool leftMousePreviouslyPressed = false;
};
//This is just a base template, for the final project, version 0.0.1 