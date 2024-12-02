#pragma once

#include <functional>
#include "ResourceIdentifiers.h"

class Settings;

namespace sf
{
    class RenderTexture;
    class Time;
}

class World final
{

public:
    explicit World(sf::RenderTexture& gameRenderTexture, const FontHolder& font, const Settings& settings, const std::function<void()>& endGameCallback);
    ~World();

    World(const World&) = delete;
    World& operator=(const World&) = delete;

    World(World&&) = delete;
    World& operator=(World&&) = delete;

    void update(sf::Time) const;
    void draw() const;
    
private:
    struct Impl;
    std::unique_ptr<Impl> mImpl;
};
