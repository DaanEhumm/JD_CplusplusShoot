#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "AR.h"
#include <vector>
#include <optional>
#include "Bullet.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800u, 600u }), "Shooter 1v1 - Test Fire");
    window.setFramerateLimit(60);

    AR ar;
    std::vector<Bullet> bullets;
    sf::Clock clock;

    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Blue);
    player.setPosition({ 375.f, 275.f });

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        // Player movement
        float playerSpeed = 200.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            player.move({ -playerSpeed * deltaTime, 0.f });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            player.move({ playerSpeed * deltaTime, 0.f });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            player.move({ 0.f, -playerSpeed * deltaTime });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            player.move({ 0.f, playerSpeed * deltaTime });

        // Shooting with left mouse button
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2f playerCenter = player.getPosition() + sf::Vector2f(player.getSize().x / 2, player.getSize().y / 2);
            sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(mousePosWindow);

            sf::Vector2f direction = mousePos - playerCenter;

            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length != 0.f)
                direction /= length;

            ar.shoot(playerCenter, direction, bullets);
        }

        for (auto& bullet : bullets) {
            bullet.update(deltaTime);
        }

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
            [&window](Bullet& b) { return b.isOffScreen(window); }),
            bullets.end());

        window.clear();
        window.draw(player);
        for (auto& bullet : bullets) {
            bullet.draw(window);
        }
        window.display();
    }

    return 0;
}


    
    