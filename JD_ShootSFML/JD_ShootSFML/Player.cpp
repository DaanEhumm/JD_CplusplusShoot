#include "Player.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include "SFMLHandler.h"
Player::Player()
    : Sprite(SFMLHandler::GetTexture("assets/textures/pistol.png")), Health(100.f)
{
    /* body.setSize({20.f, 20.f});
 body.setFillColor(sf::Color::Blue);
 body.setPosition({ 375.f, 275.f });
 */
 weapons.emplace_back(std::make_unique<AR>());
 weapons.emplace_back(std::make_unique<Pistol>()); 
}

void Player::update(float deltaTime, sf::RenderWindow& window, std::vector<Bullet>& bullets) {
    float speed = 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) Sprite.move(sf::Vector2f(-speed * deltaTime, 0));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) Sprite.move(sf::Vector2f(speed * deltaTime, 0));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) Sprite.move(sf::Vector2f(0, -speed * deltaTime));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) Sprite.move(sf::Vector2f(0, speed * deltaTime));



    sf::FloatRect bounds = Sprite.getLocalBounds();
    sf::Vector2f center = Sprite.getPosition() + (bounds.size / 2.f);


    auto& gun = weapons[currentWeaponIndex];
    gun->setPosition(center, window);
    gun->update(deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) currentWeaponIndex = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) currentWeaponIndex = 1;

    bool leftMouse = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    if ((currentWeaponIndex == 0 && leftMouse) || (currentWeaponIndex == 1 && leftMouse && !leftMousePreviouslyPressed)) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Vector2f dir = mousePos - center;
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len != 0) dir /= len;
        gun->tryShoot(center, dir, bullets);
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
            //end game place holder for now: 
            std::exit(0);  
        }
}
