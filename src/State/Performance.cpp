#include "Performance.h"
#include "CircularBuffer.h"
#include "Memory.h"

#include <imgui.h>

namespace
{
    constexpr auto flags = ImGuiWindowFlags_AlwaysAutoResize;
    constexpr size_t MaxSampleSize {10000}; // 40kb
    constexpr float GraphHeight = 40.0f;

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
        buffer.maxValue(),
        ImVec2(0, height)
        );
    }

    void framesPerSecond(const float delta)
    {
        const float fps = 1.f / delta;
        ImGui::Text("fps %.2f", fps);

        lineGraph(frames, fps, GraphHeight);
    }

    void processMemory()
    {
        const float memoryMb = Memory::getProcessMemoryUsageMB();

        ImGui::Text("Process memory %.2f MB", memoryMb);
        lineGraph(memory, memoryMb, GraphHeight);
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