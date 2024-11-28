#include "Performance.h"

#include <imgui-SFML.h>
#include <imgui.h>

#include "CircularBuffer.h"
#include "Memory.h"

namespace
{
    constexpr auto flags =
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar
    ;
    constexpr size_t MaxSampleSize {10000}; // 40kb

    CircularBuffer<float, MaxSampleSize> frames;
    CircularBuffer<float, MaxSampleSize> memory;


    void lineGraph(CircularBuffer<float, MaxSampleSize>& buffer, const float value, const float height)
    {
        buffer.push_back(value);
        ImGui::PlotLines("", [](void* delta, const int index)
        {
            const auto* bufferDelta = static_cast<CircularBuffer<float, MaxSampleSize>*>(delta);
            return bufferDelta->data()[index];
        },
        &buffer,
        static_cast<int>(buffer.size()),
        0,
        nullptr,
        0,
        *std::ranges::max_element(buffer),
        ImVec2(0, height)
        );
    }

    void framesPerSecond(const float delta)
    {
        const float fps = 1.f / delta;
        ImGui::Text("fps %.2f", fps);

        lineGraph(frames, fps, 40);
    }

    void processMemory()
    {
        const float memoryMb = Memory::getProcessMemoryUsageMB();

        ImGui::Text("Process memory %.2f MB", memoryMb);
        lineGraph(memory, memoryMb, 40);
    }

}

void Performance::update(const float delta)
{
    ImGui::Begin("Performance", nullptr, flags);
    ImGui::PushItemWidth(300.0f);

    framesPerSecond(delta);
    processMemory();

    ImGui::PopItemWidth();
    ImGui::End();
}