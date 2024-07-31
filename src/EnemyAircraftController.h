#ifndef CMAKESFMLPROJECT_ENEMY_AIRCRAFT_CONTROLLER_H
#define CMAKESFMLPROJECT_ENEMY_AIRCRAFT_CONTROLLER_H

#include "SceneNode.h"
#include "Aircraft.h"
#include "ResourceIdentifiers.h"

class EnemyAircraftController : public SceneNode
{
    public:
                                    EnemyAircraftController(const TextureHolder& textures, Aircraft::Type type, sf::Vector2f position);
        void                        tick(sf::Time, float speed);

    private:
        void                        accelerate(float speed);
        void                        spawn();

    private:
        std::vector<Aircraft*>      mAircrafts;
        const TextureHolder&        mTexture;
        Aircraft::Type              mAircraftType;
        float                       mTimeSinceLastSpawn;
        sf::Vector2f                mStartPosition;
};

#endif // CMAKESFMLPROJECT_ENEMY_AIRCRAFT_CONTROLLER_H