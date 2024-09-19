#pragma once

#include "EntitySystem.h"
#include "BackgroundEntity.h"
#include "ResourceIdentifiers.h"

class BackgroundController final
{
public:
    explicit BackgroundController(
        EntitySystem<BackgroundEntity>& entitySystem,
        TextureHolder& texture,
        sf::Vector2u bounds,
        float scrollSpeed
    );

    BackgroundController(BackgroundController&) = delete;
    BackgroundController& operator=(BackgroundController&) = delete;

    BackgroundController(BackgroundController&&) = delete;
    BackgroundController& operator=(BackgroundController&&) = delete;

    ~BackgroundController() noexcept = default;
};
