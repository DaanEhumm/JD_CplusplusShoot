#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <optional>
#include "GameManager.h"

int main() {
    SFMLHandler::Init();
    GameManager game;
    game.run();
    return 0;
}



    
    