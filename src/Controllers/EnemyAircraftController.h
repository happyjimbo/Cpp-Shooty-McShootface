#pragma once

#include "Entity/AircraftEntity.h"
#include "ResourceIdentifiers.h"
#include "EntitySystem.h"

class EnemyAircraftController final
{
public:
    EnemyAircraftController(
        EntitySystem<AircraftEntity>& entitySystem,
        ProjectileController& projectileController,
        const TextureHolder& textures,
        AircraftEntity::Type type,
        sf::Vector2f position,
        sf::FloatRect worldBounds
    );

    void tick(const sf::Time&, float speed);
    void removeEntity(AircraftEntity* entity) const;
    const std::vector<AircraftEntity*>& getEntities() const;

private:
    void accelerate(float speed) const;
    void spawn();
    void checkBounds() const;

    ProjectileController& mProjectileController;
    const TextureHolder& mTexture;
    AircraftEntity::Type mAircraftType;
    EntitySystem<AircraftEntity>& mEntitySystem;

    float mTimeSinceLastSpawn {};
    sf::Vector2f mStartPosition;
    sf::FloatRect mWorldBounds;
};
