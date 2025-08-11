#include "Player.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include "SFMLHandler.h"
Player::Player()
    : Sprite(SFMLHandler::GetTexture("assets/textures/player.png")), Health(100.f)
{
    const sf::FloatRect bounds = Sprite.getLocalBounds();
    Sprite.setOrigin({ bounds.position.x + bounds.size.x * 0.5f, bounds.position.y + bounds.size.y });

    Sprite.setScale({ 1.2f, 1.2f }); 

    constexpr float GROUND_Y = 555.f; 
    Sprite.setPosition({ 375.f, GROUND_Y });

    weapons.emplace_back(std::make_unique<AR>());

}

void Player::update(float deltaTime, sf::RenderWindow& window, std::vector<Bullet>& bullets, float worldOffsetX) {
    float speed = 200.f;
    wantsToMoveRightPastLimit = false;

    // Handle player movement
    const float PLAYER_RIGHT_LIMIT = 700.f; // max x for player on screen
    bool movingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
   
    if (movingRight) {
        if (Sprite.getPosition().x < PLAYER_RIGHT_LIMIT) {
            Sprite.move(sf::Vector2f(speed * deltaTime, 0));
        }
        else {
            wantsToMoveRightPastLimit = true;
        }
    }

	const float PLAYER_LEFT_LIMIT = 30.f;
	bool movingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
	if (movingLeft) {
		if (Sprite.getPosition().x > PLAYER_LEFT_LIMIT) {
			Sprite.move(sf::Vector2f(-speed * deltaTime, 0));
		}
	}
  

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
        sf::Vector2f playerWorldPos = Sprite.getPosition() + sf::Vector2f(worldOffsetX, 0.f);
        gun->tryShoot(playerWorldPos, dir, bullets, worldOffsetX);
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
