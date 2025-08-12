#pragma once
#include <vector>
#include <string>
#include "CharacterStates.h"
#include <SFML/Graphics.hpp>
class Animation
{
public:
    std::vector<std::string> files;
    float interval;
    float elapsed;
    
    static std::vector < std::string > AttackFiles;
    CharacterState condition;
    Animation(const std::vector<std::string>& files, float interval, sf::Sprite& sprite, CharacterState con);
    void CheckCondition(CharacterState State);
    sf::Sprite& Sprite;
    static std::vector < std::string > EnemyFiles;
private: 
    int index;
    void PlayAnimation();
};
