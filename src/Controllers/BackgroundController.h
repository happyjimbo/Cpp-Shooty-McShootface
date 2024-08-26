#pragma once

#include "EntitySystem.h"
#include <Resource/ResourceIdentifiers.h>
#include "SpriteEntity.h"

class BackgroundController final
{
public:
    explicit BackgroundController(
        EntitySystem<SpriteEntity>& entitySystem,
        TextureHolder& texture,
        sf::Vector2u bounds,
        float scrollSpeed
    );
    ~BackgroundController();
    void create();
    void tick(sf::Time delta) const;

private:
    std::vector<SpriteEntity*> mBackgroundSprites {};
    std::vector<SpriteEntity*> mCloudSprites {};

    TextureHolder& mTexture;
    const sf::Vector2f mBounds;

    const float mScrollSpeedBackground;
    const float mScrollSpeedClouds;

    EntitySystem<SpriteEntity>& mEntitySystem;

    sf::IntRect cloudRect;
};
