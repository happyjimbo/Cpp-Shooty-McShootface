#ifndef CMAKESFMLPROJECT_GAME_H
#define CMAKESFMLPROJECT_GAME_H

#include <SFML/Graphics.hpp>
#include "World.h"

class Game : private sf::NonCopyable
{

public:
                            Game();
    void                    run();
    void                    draw();

private:
    void                    processEvents();
    void                    render();
    void                    update(sf::Time);

private:
    static const sf::Time   TimePerFrame;
    sf::RenderWindow        mWindow;
    World                   mWorld;

};


#endif //CMAKESFMLPROJECT_GAME_H
