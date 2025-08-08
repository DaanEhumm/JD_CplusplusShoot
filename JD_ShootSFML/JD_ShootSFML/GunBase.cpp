#include "GunBase.h"  
#include <algorithm>  
#include <cmath>  
#include <SFML/Window/Keyboard.hpp>  
#include <SFML/System.hpp>  
#include <SFML/Graphics.hpp>

#include <SFML/System/Angle.hpp>

void GunBase::tryShoot(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets) {  
  if (canShoot()) {  
      spawnBullet(position, direction, bullets);  
      currentAmmo--;  
      fireClock.restart();  

      showFlash = true;  
      flashClock.restart();

      sf::Vector2f flashOffset(22.f, -16.f);

      float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
      float rad = angle * 3.14159f / 180.f;

      sf::Vector2f rotatedOffset(
          flashOffset.x * std::cos(rad) - flashOffset.y * std::sin(rad),
          flashOffset.x * std::sin(rad) + flashOffset.y * std::cos(rad)
      );

      muzzleFlash.setSize({ 10.f, 3.f });  
      muzzleFlash.setFillColor(sf::Color::Yellow);  
      muzzleFlash.setPosition(position + rotatedOffset + direction * 30.f);
      muzzleFlash.setRotation(sf::degrees(std::atan2(direction.y, direction.x)));
  }  
  else if (!isReloading && currentAmmo <= 0 && reserveAmmo > 0) {  
      reload();  
  }  
}

void GunBase::reload() {
    isReloading = true;
    reloadClock.restart();
}

bool GunBase::canShoot() const {
    return !isReloading && currentAmmo > 0 && fireClock.getElapsedTime().asSeconds() >= fireCooldown;
}

void GunBase::update(float deltaTime) {
    if (isReloading && reloadClock.getElapsedTime().asSeconds() >= reloadTime) {
        int toReload = std::min(magazineSize - currentAmmo, reserveAmmo);
        currentAmmo += toReload;
        reserveAmmo -= toReload;
        isReloading = false;
    }
}

void GunBase::draw(sf::RenderWindow& window) {
    if (sprite) {
        window.draw(*sprite);
    }

    if (showFlash && flashClock.getElapsedTime().asSeconds() < 0.05f) {
        window.draw(muzzleFlash);
    }
    else {
        showFlash = false;
    }
}