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
    bool isPaused {};

    GameSettingsData settings = GameSettings::getSettings();

    int width = settings.width;
    int height = settings.height;
    int fps = settings.fps;
    bool mute = settings.mute;

    void draw()
    {
#ifdef EDITOR_MODE
        ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::PushItemWidth(70.0f);
        ImGui::Checkbox("Pause", &isPaused);
        ImGui::Checkbox("Mute", &mute);

        Input(width, "width");
        Input(height, "height");
        Input(fps, "fps");

        if (ImGui::Button("Save"))
        {
            const GameSettingsData data {settings.title, width, height, fps, mute};
            GameSettings::updateSettings(data);
        }
        ImGui::PopItemWidth();

        ImGui::End();
#endif

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
    return mImpl->mute;
}