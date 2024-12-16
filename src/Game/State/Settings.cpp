#include "Settings.h"

#ifdef EDITOR_MODE
#include <string>
#include <imgui.h>
#include <iostream>
#endif

#include "GameSettings.h"
#include "GameSettingsData.h"

#ifdef EDITOR_MODE
namespace
{
    void Input(int& property, const char* label)
    {
        char propertyText[8];
        snprintf(propertyText, sizeof(propertyText), "%d", property);

        if (ImGui::InputText(label, propertyText, sizeof(propertyText)))
        {
            try
            {
                property = std::stoi(propertyText);
            }
            catch (const std::invalid_argument& e)
            {
                property = 0;
            }
        }
    }

}
#endif

struct Settings::Impl
{
    std::shared_ptr<GameSettings> gameSettings;
    GameSettingsData settings;
    bool isPaused {};

    explicit Impl(std::shared_ptr<GameSettings> gSettings) noexcept
    : gameSettings(std::move(gSettings))
    , settings(gameSettings ? gameSettings->getGameSettingsData() : GameSettingsData{})
    {
        assert(gameSettings && "GameSettings must not be null");
    }

    void draw()
    {
#ifdef EDITOR_MODE
        ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::PushItemWidth(70.0f);
        ImGui::Checkbox("Pause", &isPaused);
        ImGui::Checkbox("Mute", &settings.mute);

        Input(settings.width, "width");
        Input(settings.height, "height");
        Input(settings.fps, "fps");

        if (ImGui::Button("Save"))
        {
            gameSettings->updateSettings(settings);
        }
        ImGui::PopItemWidth();

        ImGui::End();
#endif

    }
};

Settings::Settings(std::shared_ptr<GameSettings> gameSettings) noexcept
: mImpl(std::make_unique<Impl>(std::move(gameSettings)))
{

}

Settings::~Settings() noexcept = default;

void Settings::draw() const
{
    mImpl->draw();
}

bool Settings::isPaused() const
{
    return mImpl->isPaused;
}

bool Settings::isMuted() const
{
    return mImpl->settings.mute;
}