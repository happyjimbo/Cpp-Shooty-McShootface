#pragma once

#include "EntitySystem.h"
#include "ResourceIdentifiers.h"
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

    TextureHolder& mTexture;
    const sf::Vector2f mBounds;
    const float mScrollSpeed;

    EntitySystem<SpriteEntity>& mEntitySystem;
};
