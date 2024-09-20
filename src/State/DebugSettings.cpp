#include "DebugSettings.h"

#include <imgui.h>

using Debug::DebugSettings;

struct DebugSettings::Impl
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

DebugSettings::DebugSettings() noexcept : mImpl(std::make_unique<Impl>()) {}
DebugSettings::~DebugSettings() noexcept = default;

void DebugSettings::draw() const
{
    mImpl->draw();
}

bool DebugSettings::isPaused() const
{
    return mImpl->isPaused;
}

bool DebugSettings::isMuted() const
{
    return mImpl->isMuted;
}