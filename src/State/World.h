#pragma once

#include <functional>
#include "ResourceIdentifiers.h"

namespace sf
{
    class Time;
    class RenderWindow;
}

class World final
{

public:
    explicit World(sf::RenderWindow& window, const FontHolder& font, const std::function<void()>& endGameCallback);
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
