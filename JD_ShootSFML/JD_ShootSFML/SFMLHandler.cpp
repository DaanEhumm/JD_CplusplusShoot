#include "SFMLHandler.h"
#include <iostream>
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
    window.clear(sf::Color(30, 30, 30));  
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


#include <unordered_map>

sf::Texture& SFMLHandler::GetTexture(const std::string& Path) {
    static std::unordered_map<std::string, sf::Texture> textures;

    std::unordered_map<std::string, sf::Texture>::iterator it = textures.find(Path);
    if (it != textures.end()) {
        return it->second; 
    }


    sf::Texture texture;
    if (!texture.loadFromFile(Path)) {
        std::cout << "Path could not be found (texture loading issue):" << Path << std::endl;
     
    }

    textures[Path] = std::move(texture);  // store texture in map
    return textures[Path];  // return reference to stored texture
}


sf::Sprite  SFMLHandler::RenderSprite(sf::Texture& Texture, float X, float Y) {
    sf::Sprite sprite(Texture);
    sf::Vector2 myvector = sf::Vector2(X, Y);
    sprite.setPosition(myvector);
    return sprite;
}



float SFMLHandler::getDeltaTime() {
    return deltaTime;
}