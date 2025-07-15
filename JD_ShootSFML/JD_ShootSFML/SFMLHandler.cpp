#include "SFMLHandler.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/System/Clock.hpp>

SFMLHandler::SFMLHandler(unsigned int width, unsigned int height, const std::string& title)
    : window(sf::VideoMode({ width, height }), title), deltaTime(0.0f) {
    window.setFramerateLimit(60);
}

void SFMLHandler::processEvents() {
    std::optional<sf::Event> event;
    while ((event = window.pollEvent())) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }

    deltaTime = clock.restart().asSeconds();
}

void SFMLHandler::clear() {
    window.clear(sf::Color::Black);  
}

void SFMLHandler::display() {
    window.display();
}

bool SFMLHandler::isOpen() const {
    return window.isOpen();
}

sf::RenderWindow& SFMLHandler::getWindow() {
    return window;
}

float SFMLHandler::getDeltaTime() {
    return deltaTime;
}