#pragma once

#include "ProjectileEntity.h"
#include "EntitySystem.h"

class SoundEffects;

class ProjectileInitializer final
{
public:
    explicit ProjectileInitializer(EntitySystem<ProjectileEntity>& entitySystem, const TextureHolder& texture, sf::FloatRect worldBounds, SoundEffects& soundEffects);
    void spawn(ProjectileEntity::Type type, sf::Vector2f spawnPosition) const;

private:
    EntitySystem<ProjectileEntity>& mEntitySystem;
    const TextureHolder& mTexture;
    const sf::FloatRect mWorldBounds;
    SoundEffects& mSoundEffects;
};
