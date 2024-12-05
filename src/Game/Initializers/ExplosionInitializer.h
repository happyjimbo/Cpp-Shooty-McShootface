#pragma once

#include "EntitySystem.h"
#include "ExplosionEntity.h"
#include "ResourceIdentifiers.h"

class SoundEffects;

class ExplosionInitializer final
{
public:
    explicit ExplosionInitializer(EntitySystem<ExplosionEntity>& entitySystem, TextureHolder& texture, SoundEffects& soundEffects) noexcept;
    ~ExplosionInitializer() noexcept = default;

    void spawn(const sf::Vector2f& spawnPosition, Textures::ID textureId, Sounds::ID soundId);

private:
    EntitySystem<ExplosionEntity>& mEntitySystem;
    TextureHolder& mTexture;
    sf::IntRect mExplosionRect;
    SoundEffects& mSoundEffects;
};
