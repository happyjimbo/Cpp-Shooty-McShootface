#ifndef CMAKESFMLPROJECT_PROJECTILE_CONTROLLER_H
#define CMAKESFMLPROJECT_PROJECTILE_CONTROLLER_H

#include <vector>

#include "Projectile.h"

class EntitySystem;

class ProjectileController final {

    private:
        enum Position {
            Left,
            Right
        };

    public:
                                                    ProjectileController(EntitySystem& entitySystem, const TextureHolder& texture, sf::FloatRect worldBounds);
        void                                        spawn(Projectile::Type type, sf::Vector2f spawnPosition);
        void                                        tick(sf::Time delta, float speed);
        std::vector<std::shared_ptr<Projectile>>&   getProjectiles();
        void                                        destroy(std::shared_ptr<Projectile>& projectile);

    private:
        void accelerate(float speed) const;
        void checkBounds();

    private:
        EntitySystem&                               mEntitySystem;
        std::vector<std::shared_ptr<Projectile>>    mProjectiles;
        const TextureHolder&                        mTexture;
        const sf::FloatRect                         mWorldBounds;
        float                                       mTimeSinceLastSpawn;
        Position                                    mPosition;
        const float                                 mXOffsetAmount = 15.f;
        const float                                 mYOffsetAmount = 5.f;
};

#endif // CMAKESFMLPROJECT_PROJECTILE_CONTROLLER_H