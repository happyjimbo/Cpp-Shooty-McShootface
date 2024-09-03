#include "Game.h"

#include <iostream>

const sf::Time Game::TimePerFrame = sf::seconds(sSeconds);

Game::Game()
: mWindow(sf::VideoMode(sScreenWidth, sScreenHeight), sTitle, sf::Style::Close)
{
    startGame();
    mWindow.setKeyRepeatEnabled(false);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    mWindow.setFramerateLimit(144);

    while (mWindow.isOpen())
    {
        const sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > TimePerFrame)
        {

            timeSinceLastUpdate -= TimePerFrame;

            processWindowEvents();
            update(TimePerFrame);

            render();
        }
    }
}

void Game::update(const sf::Time elapsedTime) const
{
    if (mWorld)
    {
        mWorld->update(elapsedTime);
    }
}

void Game::processWindowEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mWindow.close();
        }
    }
}

void Game::render()
{
    mWindow.clear();

    if (mWorld)
    {
        mWorld->draw();
    }

    if (mGameOver)
    {
        mGameOver->draw();
    }

    mWindow.setView(mWindow.getDefaultView());
    mWindow.display();
}

void Game::startGame()
{
    //mWorld = std::make_unique<World>(mWindow, [this]() { endGame(); });
    mWorld = new World(mWindow, [this]() { endGame(); });
}

void Game::endGame()
{
    std::cout << "end game" << std::endl;
    //mWorld.reset();
    delete mWorld;
    mWorld = nullptr;

    mGameOver = new GameOver(mWindow);
}


Game::~Game() noexcept
{
    delete mWorld;
    delete mGameOver;
}