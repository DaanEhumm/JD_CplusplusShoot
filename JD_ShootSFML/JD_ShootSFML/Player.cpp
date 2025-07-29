#include "Player.h"
#include "AR.h"
#include <SFML/Graphics.hpp>

Player::Player() {
    body.setSize({ 5.f, 5.f });
    body.setFillColor(sf::Color::Blue);
    body.setPosition({ 375.f, 275.f });
    gun = new AR();
}

void Player::update(float deltaTime, sf::RenderWindow& window, std::vector<Bullet>& bullets) {
    float speed = 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        body.move(sf::Vector2f(-speed * deltaTime, 0.f));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        body.move(sf::Vector2f(speed * deltaTime, 0.f));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        body.move(sf::Vector2f(0.f, -speed * deltaTime));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        body.move(sf::Vector2f(0.f, speed * deltaTime));

    sf::Vector2f center = body.getPosition() + body.getSize() / 2.f;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2f center = body.getPosition() + body.getSize() / 2.f;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldMouse = window.mapPixelToCoords(mousePos);

        sf::Vector2f direction = worldMouse - center;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0.f)
            direction /= length;

        gun->shoot(center, direction, bullets);
    }
    gun->setPosition(center, window);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(body);
    gun->draw(window);
}