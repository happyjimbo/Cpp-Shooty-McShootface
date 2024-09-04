#pragma once

#include "EntitySystem.h"
#include "ExplosionEntity.h"
#include "ResourceIdentifiers.h"

class ExplosionController final
{
public:
    explicit ExplosionController(EntitySystem<ExplosionEntity>& entitySystem, TextureHolder& texture) noexcept;
    ~ExplosionController() noexcept = default;

    void spawn(const sf::Vector2f& spawnPosition, Textures::ID textureId);

private:
    EntitySystem<ExplosionEntity>& mEntitySystem;
    TextureHolder& mTexture;
    sf::IntRect explosionRect;
};
