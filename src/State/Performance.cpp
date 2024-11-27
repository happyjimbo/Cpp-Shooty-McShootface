#include "Performance.h"

#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

#include "os/Memory.h"


namespace
{
    std::deque<float> frames;
    std::deque<float> memory;

    constexpr size_t maxSampleSize {10000};

    void lineGraph(std::deque<float>& deque, const float value, const float height)
    {
        deque.push_back(value);

        if (deque.size() > maxSampleSize)
        {
            deque.pop_front();
        }

        if (!deque.empty())
        {
            ImGui::PlotLines("", [](void* delta, const int index)
            {
                const auto* dequeDelta = static_cast<std::deque<float>*>(delta);
                return (*dequeDelta)[index];
            },
            &deque,
            static_cast<int>(deque.size()),
            0,
            nullptr,
            0,
            *std::ranges::max_element(deque),
            ImVec2(0, height)
            );
        }
    }

    void framesPerSecond(const float delta)
    {
        const float fps = 1.f / delta;
        ImGui::Text("fps %f", fps);

        lineGraph(frames, fps, 40);
    }

    void processMemory()
    {
        const float memoryMb = Memory::getProcessMemoryUsageMB();

        ImGui::Text("Process memory %f MB", memoryMb);
        lineGraph(memory, memoryMb, 40);
    }

}

void Performance::update(const float delta) const
{
    const_cast<Performance*>(this)->update(delta);
}


void Performance::update(const float delta)
{
    constexpr auto flags =
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar
    ;

    ImGui::Begin("Performance", nullptr, flags);
    ImGui::PushItemWidth(300.0f);

    framesPerSecond(delta);
    processMemory();

    ImGui::PopItemWidth();
    ImGui::End();
}