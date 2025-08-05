#include "Enemey.h"
#include "SFMlHandler.h"
#include <cmath>


Enemy::Enemy()
    : Sprite(SFMLHandler::GetTexture("texture")), Health(100.f), Speed(100.f) // verrander texture naar jou texture
{
}


void Enemy::Move(const sf::Vector2f& targetPosition)
{
    sf::Vector2f currentPos = Sprite.getPosition();
    sf::Vector2f direction = targetPosition - currentPos;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y); // heel simpel A^2 + B^2 = C^2, om de afstand te berekenen.

    if (distance > 0.1f)
    {
        sf::Vector2f directionNorm = direction / distance;

        
        float deltaTime = 1.f / 60.f; // 60 = aantal frames, mag ook hoger kost wel meer kracht tho.

        sf::Vector2f movement = directionNorm * Speed * deltaTime;

        if ((movement.x * movement.x + movement.y * movement.y) > (distance * distance))
            Sprite.setPosition(targetPosition);
        else
            Sprite.move(movement);
    }
}
