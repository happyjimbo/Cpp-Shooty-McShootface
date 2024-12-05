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

    explicit StarInitializer(const StarInitializer&) = delete;
    StarInitializer& operator=(const StarInitializer&) = delete;

    explicit StarInitializer(StarInitializer&&) = delete;
    StarInitializer& operator=(StarInitializer&&) = delete;

    StarEntity& getStarEntity() const;
private:
    StarEntity* mStarEntity;

};
