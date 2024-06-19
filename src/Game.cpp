//
// Created by James Woodward on 19/06/2024.
//

#include "Logger.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

sf::CircleShape createShape(float x, float y, float radius, sf::Color color) {
    sf::CircleShape shape;
    shape.setRadius(radius);
    shape.setPosition(x, y);
    shape.setFillColor(color);
    return shape;
}

Game::Game()
: mWindow(sf::VideoMode(640, 480), "World", sf::Style::Close)
{
    Log("Init Game");
}

void Game::run()
{
    mWindow.setFramerateLimit(144);

    sf::CircleShape shape = createShape(100.f, 100.f, 40.f, sf::Color::Cyan);
    sf::CircleShape secondShape = createShape(200.f, 200.f, 40.f, sf::Color::Blue);

    while (mWindow.isOpen())
    {
        processEvents();
        render(shape, secondShape);
    }
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        switch (event.type) {

            case sf::Event::KeyPressed:
                Log("Key Pressed");
                break;

            case sf::Event::KeyReleased:
                Log("Key Released");
                break;

            case sf::Event::Closed:
                mWindow.close();
                break;
        }
    }
}

void Game::render(sf::CircleShape shape, sf::CircleShape secondShape)
{
    mWindow.clear();
    mWindow.draw(shape);
    mWindow.draw(secondShape);
    mWindow.setView(mWindow.getDefaultView());
    mWindow.display();
}