#ifndef CMAKESFMLPROJECT_ENEMY_AIRCRAFT_CONTROLLER_H
#define CMAKESFMLPROJECT_ENEMY_AIRCRAFT_CONTROLLER_H

#include "SceneNode.h"
#include "Aircraft.h"
#include "ResourceIdentifiers.h"

class EnemyAircraftController final : public SceneNode {

    public:
                                        EnemyAircraftController(
                                            const TextureHolder& textures,
                                            const Aircraft::Type type,
                                            const sf::Vector2f position,
                                            const sf::FloatRect worldBounds
                                        );

        void                                            tick(const sf::Time&, const float speed);
        std::vector<std::shared_ptr<Aircraft>>&          getAircrafts();
        void                                            destroy(const std::shared_ptr<Aircraft>& aircraft);

    private:
        void                            accelerate(float speed) const;
        void                            spawn();
        void                            checkBounds() ;

    private:
        std::vector<std::shared_ptr<Aircraft>>          mAircrafts;
        const TextureHolder&                            mTexture;
        Aircraft::Type                                  mAircraftType;
        float                                           mTimeSinceLastSpawn;
        sf::Vector2f                                    mStartPosition;
        sf::FloatRect                                   mWorldBounds;
};

#endif // CMAKESFMLPROJECT_ENEMY_AIRCRAFT_CONTROLLER_H