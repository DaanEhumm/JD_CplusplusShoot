#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include "Bullet.h"

class GunBase {
public:
    virtual ~GunBase() = default;

    void tryShoot(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets);
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow& window);
    virtual void setPosition(const sf::Vector2f& pos, sf::RenderWindow& window) = 0;

protected:
    int magazineSize = 10;
    int currentAmmo = 10;
    int reserveAmmo = 30;

    float reloadTime = 1.5f;
    bool isReloading = false;
    sf::Clock reloadClock;

    float fireCooldown = 0.3f;
    sf::Clock fireClock;

    bool showFlash = false;
    sf::Clock flashClock;
    sf::RectangleShape muzzleFlash;

    sf::Vector2f aimDir;

    std::optional<sf::Sprite> sprite;

    sf::Texture bulletTexture;

    virtual void spawnBullet(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets) = 0;
    void reload();
    bool canShoot() const;
};