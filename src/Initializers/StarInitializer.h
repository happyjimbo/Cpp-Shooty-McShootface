#pragma once
#include "EntitySystem.h"
#include "ResourceIdentifiers.h"

class StarEntity;

class StarInitializer final
{
public:
    explicit StarInitializer(
        EntitySystem<StarEntity>& entitySystem,
        const TextureHolder& textures
    );

    ~StarInitializer() = default;

    explicit StarInitializer(StarInitializer&) = delete;
    StarInitializer& operator=(StarInitializer&) = delete;

    explicit StarInitializer(StarInitializer&&) = delete;
    StarInitializer& operator=(StarInitializer&&) = delete;
};
