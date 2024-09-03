#include "Game.h"

#include "MediaFiles.h"

const sf::Time Game::TimePerFrame = sf::seconds(sSeconds);

Game::Game()
: mWindow(sf::VideoMode(sScreenWidth, sScreenHeight), sTitle, sf::Style::Close)
{
    mFont.load(Fonts::Main, MediaFiles::Font);
    mStateHandler = new StateHandler(mWindow, mFont);

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
    mStateHandler->update(elapsedTime);
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

        mStateHandler->processWindowEvents(event);
    }
}

void Game::render()
{
    mWindow.clear();

    mStateHandler->draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.display();
}


Game::~Game() noexcept
{
    delete mStateHandler;
}

