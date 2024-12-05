#pragma once

#include "EntitySystem.h"
#include "BackgroundEntity.h"
#include "ResourceIdentifiers.h"

class BackgroundInitializer final
{
public:
    explicit BackgroundInitializer(
        EntitySystem<BackgroundEntity>& entitySystem,
        TextureHolder& texture,
        sf::Vector2u bounds,
        float scrollSpeed
    );

    BackgroundInitializer(const BackgroundInitializer&) = delete;
    BackgroundInitializer& operator=(const BackgroundInitializer&) = delete;

    BackgroundInitializer(BackgroundInitializer&&) = delete;
    BackgroundInitializer& operator=(BackgroundInitializer&&) = delete;

    ~BackgroundInitializer() noexcept = default;
};
