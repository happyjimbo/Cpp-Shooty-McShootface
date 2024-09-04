#pragma once

#include <SFML/Graphics/Rect.hpp>
#include "RandomFloatGenerator.h"

class SpriteEntity;

struct CloudData
{
    sf::IntRect cloudRect;
    float scrollSpeed;
    float scrollSpeedOffset;

    static float generateRandomXpos()
    {
        return generateRandomFloat(-10.f, 20.f);
    }
};
