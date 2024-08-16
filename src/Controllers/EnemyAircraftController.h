#ifndef CMAKESFMLPROJECT_ENEMY_AIRCRAFT_CONTROLLER_H
#define CMAKESFMLPROJECT_ENEMY_AIRCRAFT_CONTROLLER_H

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

    public:
        void tick(const sf::Time&, float speed);
        void removeEntity(AircraftEntity* entity) const;
        const std::vector<AircraftEntity*>& getEntities() const;

    private:
        void accelerate(float speed) const;
        void spawn();
        void checkBounds() const;

    private:
        ProjectileController& mProjectileController;
        const TextureHolder& mTexture;
        AircraftEntity::Type mAircraftType;
        float mTimeSinceLastSpawn;
        sf::Vector2f mStartPosition;
        sf::FloatRect mWorldBounds;
        EntitySystem<AircraftEntity>& mEntitySystem;
};

#endif // CMAKESFMLPROJECT_ENEMY_AIRCRAFT_CONTROLLER_H