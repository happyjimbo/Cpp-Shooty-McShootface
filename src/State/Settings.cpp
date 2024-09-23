#include "Settings.h"

#include <imgui.h>

struct Settings::Impl
{
    bool isPaused {};
    bool isMuted {};

    void draw()
    {
        ImGui::Begin("Debug");
        ImGui::Checkbox("Pause", &isPaused);
        ImGui::Checkbox("Mute", &isMuted);
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