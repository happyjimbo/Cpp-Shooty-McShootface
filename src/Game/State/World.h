#pragma once

#include <functional>

#include "EntitySystem.h"
#include "ResourceIdentifiers.h"

class EntityObject;

struct EntitySystems;
struct SoundSettings;

namespace sf
{
    class RenderTexture;
    class Time;
}

class World final
{

public:
    explicit World(sf::RenderTexture& gameRenderTexture, const FontHolder& font, const SoundSettings& soundSettings, const std::function<void()>& endGameCallback);
    ~World();

    World(const World&) = delete;
    World& operator=(const World&) = delete;

    World(World&&) = delete;
    World& operator=(World&&) = delete;

    void update(sf::Time) const;
    void draw() const;

    EntitySystems& getEntitySystems() const;
    
private:
    struct Impl;
    std::unique_ptr<Impl> mImpl;
};
