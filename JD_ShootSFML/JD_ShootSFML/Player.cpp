#include "Player.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include "SFMLHandler.h"
Player::Player()
    : Sprite(SFMLHandler::GetTexture("assets/textures/player.png")), Health(100.f)
{
    auto bounds = Sprite.getLocalBounds();
    Sprite.setOrigin(sf::Vector2(bounds.size.x / 2.f, bounds.size.y / 2.f));

    Sprite.setPosition(sf::Vector2(375.f, 500.f));
	Sprite.setScale(sf::Vector2(1.2f, 1.2f));

    weapons.emplace_back(std::make_unique<AR>());
    //weapons.emplace_back(std::make_unique<Pistol>());    omly ar for now WATCH!
}

void Player::update(float deltaTime, sf::RenderWindow& window, std::vector<Bullet>& bullets) {
    float speed = 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) Sprite.move(sf::Vector2f(-speed * deltaTime, 0));  // only right left 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) Sprite.move(sf::Vector2f(speed * deltaTime, 0));
    

    sf::Vector2f playerPos = Sprite.getPosition();
    sf::Vector2f aimDir(1.f, 0.f);
    Sprite.setRotation(sf::degrees(0.f));


    Sprite.setScale(sf::Vector2(2.8f, 2.8f));

    auto& gun = weapons[currentWeaponIndex];
    gun->setPosition(playerPos, window);
    gun->update(deltaTime);

    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) currentWeaponIndex = 0;
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) currentWeaponIndex = 1;

    bool leftMouse = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    if ((currentWeaponIndex == 0 && leftMouse) ||
        (currentWeaponIndex == 1 && leftMouse && !leftMousePreviouslyPressed)) {

        sf::Vector2f dir = aimDir;
        gun->tryShoot(playerPos, dir, bullets);
    }
    leftMousePreviouslyPressed = leftMouse;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(Sprite);
    weapons[currentWeaponIndex]->draw(window);
}

void Player::TakeDamage(int Damage) {
    Health -= Damage;
    if (Health <= 0) {
        std::exit(0);
    }
}
