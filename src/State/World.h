#pragma once

#include <memory>
#include <functional>

#include "ResourceIdentifiers.h"
#include "SFML/System/Time.hpp"

namespace Aircraft { class AircraftEntity; }
using Aircraft::AircraftEntity;

namespace sf { class RenderWindow; }

namespace GUI { class Label; }
using GUI::Label;

class WorldImpl;

class World final
{

public:
    explicit World(sf::RenderWindow& window,
        TextureHolder& textures,
        const FontHolder& font,
        const std::function<void()>& endGameCallback);
    ~World();

    World(const World&) = delete;
    World& operator=(const World&) = delete;

    World(World&&) = delete;
    World& operator=(World&&) = delete;

    void update(sf::Time);
    void draw();

private:
    std::unique_ptr<WorldImpl> impl_;
};
