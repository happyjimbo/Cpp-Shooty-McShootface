#include "Game.h"

#include "MediaFiles.h"

const sf::Time Game::TimePerFrame = sf::seconds(sSeconds);

Game::Game()
: mWindow(sf::VideoMode(sScreenWidth, sScreenHeight), sTitle, sf::Style::Close)
{
    mFont.load(Fonts::Main, MediaFiles::Font);

    transitionScreen("Shooty Mcshootface", "Play now!");
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

        if (mTransitionScreen)
        {
            mTransitionScreen->handleEvent(event, [this]()
            {
                startGame();
            });
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

    if (mTransitionScreen)
    {
        mTransitionScreen->draw();
    }

    mWindow.setView(mWindow.getDefaultView());
    mWindow.display();
}

void Game::startGame()
{
    delete mTransitionScreen;
    mTransitionScreen = nullptr;

    //mWorld = std::make_unique<World>(mWindow, mFont, [this]() { endGame(); });
    mWorld = new World(mWindow, mFont, [this]() { transitionScreen("YOU DIED", "Play again!"); });
}

void Game::transitionScreen(const char* title, const char* buttonText)
{
    delete mWorld;
    mWorld = nullptr;

    mTransitionScreen = new TransitionScreen(mWindow, mFont, title, buttonText);
}

Game::~Game() noexcept
{
    delete mWorld;
    delete mTransitionScreen;
}