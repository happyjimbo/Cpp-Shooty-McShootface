#ifndef CMAKESFMLPROJECT_ENEMY_AIRCRAFT_CONTROLLER_H
#define CMAKESFMLPROJECT_ENEMY_AIRCRAFT_CONTROLLER_H

#include <vector>

#include "Entity/AircraftEntity.h"
#include "ResourceIdentifiers.h"

class EntitySystem;

class EnemyAircraftController final
{
    public:
        EnemyAircraftController(
            EntitySystem& entitySystem,
            ProjectileController& projectileController,
            const TextureHolder& textures,
            AircraftEntity::Type type,
            sf::Vector2f position,
            sf::FloatRect worldBounds
        );

    public:

        void                                            tick(const sf::Time&, float speed);
        std::vector<std::shared_ptr<AircraftEntity>>&   getAircrafts();
        void                                            destroy(std::shared_ptr<AircraftEntity>& aircraft);

    private:
        void                            accelerate(float speed) const;
        void                            spawn();
        void                            checkBounds();

    private:
        std::vector<std::shared_ptr<AircraftEntity>>    mAircrafts;
        EntitySystem&                                   mEntitySystem;
        ProjectileController&                           mProjectileController;
        const TextureHolder&                            mTexture;
        AircraftEntity::Type                            mAircraftType;
        float                                           mTimeSinceLastSpawn;
        sf::Vector2f                                    mStartPosition;
        sf::FloatRect                                   mWorldBounds;
};

#endif // CMAKESFMLPROJECT_ENEMY_AIRCRAFT_CONTROLLER_H