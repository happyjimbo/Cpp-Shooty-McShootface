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

    ~BackgroundController() noexcept = default;

    void create() const;

private:
    EntitySystem<BackgroundEntity>& mEntitySystem;
    TextureHolder& mTexture;

    const sf::Vector2u mBounds;
    const float mScrollSpeed;
    constexpr static float sBackgroundCount {2};
};
