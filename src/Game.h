//
// Created by James Woodward on 19/06/2024.
//

#ifndef CMAKESFMLPROJECT_GAME_H
#define CMAKESFMLPROJECT_GAME_H


#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/CircleShape.hpp"

class Game {

public:
    Game();
    void run();

private:
    sf::RenderWindow mWindow;
    void processEvents();
    void render(sf::CircleShape, sf::CircleShape);

};


#endif //CMAKESFMLPROJECT_GAME_H
