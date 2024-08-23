#pragma once

#include <Entity/ProjectileEntity.h>
#include <Entity/EntitySystem.h>

class ProjectileController final
{
public:
    explicit ProjectileController(EntitySystem<ProjectileEntity>& entitySystem, const TextureHolder& texture, sf::FloatRect worldBounds);
    void spawn(ProjectileEntity::Type type, sf::Vector2f spawnPosition) const;
    void tick(sf::Time delta, float speed);

private:
    void accelerate(sf::Time delta, float speed) const;
    void checkBounds() const;

private:
    const TextureHolder& mTexture;
    const sf::FloatRect mWorldBounds;
    float mTimeSinceLastSpawn {};
    static constexpr float mSpeed = 500.f;
    EntitySystem<ProjectileEntity>& mEntitySystem;
};