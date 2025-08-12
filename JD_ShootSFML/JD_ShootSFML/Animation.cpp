#include "Animation.h"
#include "CharacterStates.h"
#include "SFMLHandler.h"
Animation::Animation(const std::vector<std::string>& files, float interval, sf::Sprite& sprite, CharacterState con)
    : files(files), interval(interval), Sprite(sprite), condition(con), index(0), elapsed(0.f)
{
}

//void SFMLHandler::RenderAnimation(sf::Sprite sprite, std::string file, float interval) {
std::vector<std::string> Animation::EnemyFiles = {
  "assets/textures/EnemyWalk1.png",
"assets/textures/EnemyWalk2.png",
"assets/textures/EnemyWalk3.png",
"assets/textures/EnemyWalk4.png",
"assets/textures/EnemyWalk5.png",
"assets/textures/EnemyWalk6.png",
"assets/textures/EnemyWalk7.png",
};


std::vector<std::string> Animation::AttackFiles = {
 "assets/textures/enemyAttack1.png",
"assets/textures/enemyAttack2.png",
"assets/textures/enemyAttack3.png",
"assets/textures/enemyAttack4.png",
"assets/textures/enemyAttack5.png",
"assets/textures/enemyAttack6.png",
"assets/textures/enemyAttack7.png",
"assets/textures/enemyAttack8.png",
"assets/textures/enemyAttack9.png",
};
void Animation::PlayAnimation() {
    elapsed += SFMLHandler::GetDeltaTime(); // get time since last frame

    if (elapsed >= interval) {
        elapsed = 0.f;
        index = (index + 1) % files.size(); // loop animation frames
    }

    SFMLHandler::RenderAnimation(Sprite, SFMLHandler::GetTexture(files[index]), interval);
}


void Animation::CheckCondition(CharacterState State) {
    if (Animation::condition == State) {
        if (index + 1 >= files.size()) {
            index = 0;
        }
        PlayAnimation();
    }
}