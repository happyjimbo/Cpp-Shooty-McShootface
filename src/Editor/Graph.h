#pragma once
#include "CircularBuffer.h"
#include <imgui.h>

namespace Graph
{
    constexpr auto flags = ImGuiWindowFlags_AlwaysAutoResize;

    template <size_t Size>
    concept ValidSize = (Size > 0);

    void beginPanel(const char* name)
    {
        ImGui::Begin(name, nullptr, flags);
        ImGui::PushItemWidth(300.0f);
    }

    template <size_t Size> requires ValidSize<Size>
    void plotGraph(const char* stat, CircularBuffer<float, Size>& buffer, const float value, const float height)
    {
        ImGui::Text(stat, value);

        buffer.push_back(value);
        ImGui::PlotLines("", [](void* delta, const int index)
        {
            const auto* bufferDelta = static_cast<CircularBuffer<float, Size>*>(delta);
            return bufferDelta->data()[index];
        },
        &buffer,
        static_cast<int>(buffer.size()),
        0,
        nullptr,
        0,/
        buffer.maxValue(),
        ImVec2(0, height)
        );
    }

    void endPanel()
    {
        ImGui::PopItemWidth();
        ImGui::End();
    }

    template <size_t Size> requires ValidSize<Size>
    void renderPanelWithGraph(const char* name, const char* stat, CircularBuffer<float, Size>& buffer, const float value, const float height)
    {
        beginPanel(name);
        plotGraph(stat, buffer, value, height);
        endPanel();
    }
}