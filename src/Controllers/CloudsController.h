#pragma once

#include "EntitySystem.h"
#include <Resource/ResourceIdentifiers.h>
#include "SpriteEntity.h"

class CloudsController final
{
public:
    explicit CloudsController(
        EntitySystem<SpriteEntity>& entitySystem,
        TextureHolder& texture,
        float scrollSpeed
    ) noexcept;

    ~CloudsController();
    void create();
    void tick(sf::Time delta) const;

private:

    static float generateRandomXpos();

    EntitySystem<SpriteEntity>& mEntitySystem;
    std::vector<SpriteEntity*> mSprites {};
    TextureHolder& mTexture;
    sf::IntRect cloudRect;

    float mScrollSpeed;
    const std::vector<float> mScrollSpeedOffsets = {0.3f, 1.f, 0.6f};
};
