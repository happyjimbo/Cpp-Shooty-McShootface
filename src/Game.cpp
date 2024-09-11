#include "Game.h"
#include "MediaFiles.h"

// #include <imgui-SFML.h>
// #include <imgui.h>

namespace
{
    constexpr const auto* sTitle = "Shooty McShootface";
    constexpr int sScreenWidth {640};
    constexpr int sScreenHeight {480};
    constexpr float sSeconds {1.f / 60.f};

    const sf::Time TimePerFrame = sf::seconds(sSeconds);
}

Game::Game()
: mWindow(sf::VideoMode(sScreenWidth, sScreenHeight), sTitle, sf::Style::Close)
{
    mFont.load(Fonts::Main, MediaFiles::Font);

    mStateHandler = std::make_unique<StateHandler>(mWindow, mFont);

    mWindow.setKeyRepeatEnabled(false);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    mWindow.setFramerateLimit(144);

    // ImGui::SFML::Init(mWindow);

    while (mWindow.isOpen())
    {
        const sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;


        while (timeSinceLastUpdate > TimePerFrame)
        {

            // ImGui::SFML::Update(mWindow, elapsedTime);
            timeSinceLastUpdate -= TimePerFrame;

            processWindowEvents();
            update(TimePerFrame);

            render();

        }
    }

    // ImGui::SFML::Shutdown();
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
        // ImGui::SFML::ProcessEvent(event);

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

    // ImGui::ShowDemoWindow();
    // ImGui::Render();

    mStateHandler->draw();

    mWindow.setView(mWindow.getDefaultView());


    // ImGui::SFML::Render(mWindow);

    mWindow.display();
}

