#pragma once
#include "GunBase.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class AR : public GunBase {
public:
	AR();
	void shoot(sf::Vector2f position, sf::Vector2f direction, std::vector<Bullet>& bullets) override;
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void setPosition(const sf::Vector2f& pos, sf::RenderWindow& window) override;

private: 
	sf::Texture texture;
	std::optional<sf::Sprite> sprite;
};