#pragma once

#include "EntitySystem.h"
#include "ResourceIdentifiers.h"

#include "CloudEntity.h"

class CloudsController final
{
public:
    explicit CloudsController(
        EntitySystem<CloudEntity>& entitySystem,
        TextureHolder& texture,
        float scrollSpeed
    ) noexcept;

    ~CloudsController() noexcept = default;
    void create() const;

private:

    EntitySystem<CloudEntity>& mEntitySystem;
    TextureHolder& mTexture;

    float mScrollSpeed;
};
