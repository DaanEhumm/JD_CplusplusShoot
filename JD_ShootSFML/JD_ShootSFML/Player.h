#pragma once
#include "Character.h"
#include "AR.h"
#include "Pistol.h"

class Player : public Character {
public:
    Player();
    void update(float deltaTime, sf::RenderWindow& window, std::vector<Bullet>& bullets) override;
    void draw(sf::RenderWindow& window) override;

private:
    std::vector<std::unique_ptr<GunBase>> weapons;
    int currentWeaponIndex = 0;
    bool leftMousePreviouslyPressed = false;
};
//This is just a base template, for the final project, version 0.0.1 