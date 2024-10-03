#include "Settings.h"

#include <string>
#include <imgui.h>
#include <iostream>

#include "GameSettings.h"
#include "GameSettingsData.h"

namespace
{
    void Input(int& property, const char* label)
    {
        char propertyText[8];  // Use a fixed-size char array
        snprintf(propertyText, sizeof(propertyText), "%d", property); // Format the int to char array

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

struct Settings::Impl
{
    bool isPaused {};
    bool isMuted {};

    GameSettingsData settings = GameSettings::getSettings();

    int width = settings.width;
    int height = settings.height;
    int fps = settings.fps;

    void draw()
    {
        ImGui::Begin("Debug");
        ImGui::Checkbox("Pause", &isPaused);
        ImGui::Checkbox("Mute", &isMuted);

        Input(width, "width");
        Input(height, "height");
        Input(fps, "fps");

        if (ImGui::Button("Save"))
        {
            const GameSettingsData data {settings.title, width, height, fps};
            GameSettings::updateSettings(data);
        }

        ImGui::End();
    }
};

Settings::Settings() noexcept : mImpl(std::make_unique<Impl>()) {}
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
    return mImpl->isMuted;
}