#include "Logger.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

/*sf::CircleShape createShape(float x, float y, float radius, sf::Color color) {
    sf::CircleShape shape;
    shape.setRadius(radius);
    shape.setPosition(x, y);
    shape.setFillColor(color);
    return shape;
}*/

Game::Game()
: mWindow(sf::VideoMode(640, 480), "World", sf::Style::Close)
, mWorld(mWindow)
{
    Log("Init Game");
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    mWindow.setFramerateLimit(144);

//    sf::CircleShape shape = createShape(100.f, 100.f, 40.f, sf::Color::Cyan);
//    sf::CircleShape secondShape = createShape(500.f, 200.f, 40.f, sf::Color::Blue);

    while (mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }


        render();
    }
}

void Game::update(sf::Time elapsedTime)
{
    mWorld.update(elapsedTime);
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        switch (event.type) {

            case sf::Event::KeyPressed:
                Log("Key Pressed " + std::to_string(static_cast<int>(event.key.code)));
                break;

            case sf::Event::KeyReleased:
                Log("Key Released " + std::to_string(static_cast<int>(event.key.code)));
                break;

            case sf::Event::Closed:
                mWindow.close();
                break;
        }
    }
}

void Game::render()
{
    mWindow.clear();

    mWorld.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.display();
}