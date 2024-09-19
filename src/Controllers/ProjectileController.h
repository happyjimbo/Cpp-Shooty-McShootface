#pragma once

#include "ProjectileEntity.h"
#include "EntitySystem.h"

class ProjectileController final
{
public:
    explicit ProjectileController(EntitySystem<ProjectileEntity>& entitySystem, const TextureHolder& texture, sf::FloatRect worldBounds);
    void spawn(ProjectileEntity::Type type, sf::Vector2f spawnPosition) const;

private:
    EntitySystem<ProjectileEntity>& mEntitySystem;
    const TextureHolder& mTexture;
    const sf::FloatRect mWorldBounds;
};