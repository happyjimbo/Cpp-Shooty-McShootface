#pragma once

#include "EntitySystem.h"
#include "ExplosionEntity.h"
#include "ResourceIdentifiers.h"

class SoundEffects;

class ExplosionController final
{
public:
    explicit ExplosionController(EntitySystem<ExplosionEntity>& entitySystem, TextureHolder& texture, SoundEffects& soundEffects) noexcept;
    ~ExplosionController() noexcept = default;

    void spawn(const sf::Vector2f& spawnPosition, Textures::ID textureId, Sounds::ID soundId);

private:
    EntitySystem<ExplosionEntity>& mEntitySystem;
    TextureHolder& mTexture;
    sf::IntRect mExplosionRect;
    SoundEffects& mSoundEffects;
};
