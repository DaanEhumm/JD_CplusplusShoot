#include "SFMLHandler.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/System/Clock.hpp>
#include <cmath>
#include <thread>
#include <chrono>


sf::RenderWindow SFMLHandler::window;
sf::Clock SFMLHandler::clock;
float SFMLHandler::deltaTime = 0.0f;



void SFMLHandler::Init() {
    window.create(sf::VideoMode(sf::Vector2u(800, 600)), "Shooter 1v1");
    window.setFramerateLimit(60);
}





void SFMLHandler::ProcessEvents() {
    std::optional<sf::Event> event;
    while ((event = window.pollEvent())) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }

    deltaTime = clock.restart().asSeconds();
}

void SFMLHandler::Clear() {
    window.clear(sf::Color(30, 30, 30));  
}

void SFMLHandler::Display() {
    window.display();
}

bool SFMLHandler::IsOpen() {
    return window.isOpen();
}

sf::RenderWindow& SFMLHandler::GetWindow() {
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



float SFMLHandler::GetDeltaTime() {
    return deltaTime;
}


bool SFMLHandler::GetCollision(const sf::Sprite& obj1, const sf::Sprite& obj2) {
    sf::FloatRect bounds1 = obj1.getLocalBounds();
    sf::FloatRect bounds2 = obj2.getLocalBounds();
    float radius1 = std::sqrt(bounds1.size.x * bounds1.size.x + bounds1.size.y * bounds1.size.y) / 2.f;
    float radius2 = std::sqrt(bounds2.size.x * bounds2.size.x + bounds2.size.y * bounds2.size.y) / 2.f;
    

    if (std::sqrt((bounds1.position.x - bounds2.position.x) + (bounds1.position.y - bounds2.position.y)) <= radius1+radius2) {
        return true;
     }
    return false;
}


void SFMLHandler::RenderAnimation(sf::Sprite& sprite, sf::RenderWindow& window, std::vector<std::string> files, float interval, float elapsed, int index) {
    elapsed += SFMLHandler::GetDeltaTime();
    if (elapsed >= interval) {
        elapsed = 0.f;
        if (index + 1 > files.size()) {
            index = 0;
        }
        sf::Texture& texture = SFMLHandler::GetTexture(files[index]);
        sprite.setTexture(texture);
        window.draw(sprite);

        RenderAnimation(sprite, window, files, interval, elapsed, index + 1);
    }
}



/*void RenderAnimation(sf::Sprite& sprite, sf::RenderWindow& window, std::vector<std::string> files, float interval, float elapsed = 0, int index = 0) {

}*/