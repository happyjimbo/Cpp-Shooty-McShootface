#include "Game.h"

#include <imgui-SFML.h>
#include "rapidcsv.h"

#include "MediaFiles.h"
#include "StateHandler.h"
#include "TransitionScreen.h"
#include "SFML/Graphics.hpp"
#include "GameSettings.h"

namespace
{
    GameSettings loadSettings()
    {
        constexpr const char* Settings = "./Media/Data/settings.csv";
        GameSettings settings;

        if (std::ifstream file(Settings); file.is_open())
        {
            rapidcsv::Document doc(Settings);
            settings.title = doc.GetCell<std::string>("title", 0);
            settings.width = doc.GetCell<int>("width", 0);
            settings.height = doc.GetCell<int>("height", 0);
            settings.fps = doc.GetCell<float>("fps", 0);
        }
        else
        {
            std::cerr << "Error: CSV file not found or cannot be opened!" << std::endl;
        }
        return settings;
    }

    GameSettings settings = loadSettings();

    const sf::Time TimePerFrame = sf::seconds(1 / settings.fps);

}

struct Game::Impl
{
    sf::RenderWindow mWindow;
    FontHolder mFont;
    std::unique_ptr<StateHandler> mStateHandler;

    explicit Impl(const GameSettings& settings)
    : mWindow(sf::VideoMode(settings.width, settings.height), settings.title, sf::Style::Close)
    {
        mFont.load(Fonts::Main, MediaFiles::Font);
        mStateHandler = std::make_unique<StateHandler>(mWindow, mFont);
        mWindow.setKeyRepeatEnabled(false);
    }

    void update(const sf::Time elapsedTime) const
    {
        mStateHandler->update(elapsedTime);
    }

    void processWindowEvents()
    {
        sf::Event event;
        while(mWindow.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
            {
                mWindow.close();
            }

            mStateHandler->processWindowEvents(event);
        }
    }

    void render()
    {
        mWindow.clear();

        mStateHandler->draw();

        ImGui::SFML::Render(mWindow);

        mWindow.setView(mWindow.getDefaultView());
        mWindow.display();
    }
};

Game::Game() noexcept : mImpl(std::make_unique<Impl>(settings)) {}
Game::~Game() noexcept = default;

void Game::run() const
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    mImpl->mWindow.setFramerateLimit(144);

    const auto success = ImGui::SFML::Init(mImpl->mWindow);

    while (success && mImpl->mWindow.isOpen())
    {
        const sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            mImpl->processWindowEvents();
            mImpl->update(TimePerFrame);
            mImpl->render();
        }
    }

    ImGui::SFML::Shutdown();
}
