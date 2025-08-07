#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>

struct RenderedSprite {
    sf::Texture texture;
    sf::Sprite sprite;
};

class SFMLHandler {
public:
    static void Init();

    static bool GetCollision(const sf::Sprite& obj1, const sf::Sprite& obj2);
    static void ProcessEvents();
    static void Clear();
    static void Display();
    static bool IsOpen();
    static sf::RenderWindow& GetWindow();
    static float GetDeltaTime();
    static sf::Sprite RenderSprite(sf::Texture& texture, float x, float y);
    static sf::Texture& GetTexture(const std::string& path);
    static void RenderAnimation(sf::Sprite& sprite, sf::RenderWindow& window, std::vector<std::string> files, float interval, float elapsed = 0, int index = 0);

private:
    static sf::RenderWindow window;
    static sf::Clock clock;
    static float deltaTime;
};
