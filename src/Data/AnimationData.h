#pragma once

#include <SFML/Graphics/Rect.hpp>

struct AnimationData
{
    int frame {};
    float timeSinceLastFrame {};
    constexpr static int spriteSize = 100;
    constexpr static int frameLimit = 6;

    void updateTimeSinceLastFrame(const float deltaTime) noexcept {
        timeSinceLastFrame += deltaTime;
    }

    sf::IntRect getAnimationRect() const
    {
        return sf::IntRect(spriteSize * frame, 0, spriteSize, spriteSize);
    }

    bool canIncreaseFrame(const float delay) const noexcept
    {
        return timeSinceLastFrame > delay && frame < frameLimit;
    }

    void nextFrame() noexcept
    {
        ++frame;
        timeSinceLastFrame = 0;
    }

    void reset() noexcept
    {
        frame = 0;
        timeSinceLastFrame = 0;
    }

    bool hasAnimationEnded() const noexcept
    {
        return frame >= frameLimit;
    }

};
