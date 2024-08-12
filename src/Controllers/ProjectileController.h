#ifndef CMAKESFMLPROJECT_PROJECTILE_CONTROLLER_H
#define CMAKESFMLPROJECT_PROJECTILE_CONTROLLER_H

#include <unordered_set>
#include <vector>

#include "Entity/ProjectileEntity.h"

class EntitySystem;

class ProjectileController final {

    private:
        enum Position {
            Left,
            Right
        };

    public:
                                                            ProjectileController(EntitySystem& entitySystem, const TextureHolder& texture, sf::FloatRect worldBounds);
        void                                                spawn(ProjectileEntity::Type type, sf::Vector2f spawnPosition);
        void                                                tick(sf::Time delta, float speed);
        std::vector<std::shared_ptr<ProjectileEntity>>&     getProjectiles();

        void                                                removeMarkedProjectiles();
        void                                                destroy(const std::shared_ptr<ProjectileEntity>& projectile);


    private:
        void                                                accelerate(sf::Time delta, float speed) const;
        void                                                checkBounds();

    private:
        EntitySystem&                                           mEntitySystem;
        std::vector<std::shared_ptr<ProjectileEntity>>          mProjectiles;
        std::unordered_set<ProjectileEntity*>                   mProjectilesToRemove;
        const TextureHolder&                        mTexture;
        const sf::FloatRect                         mWorldBounds;
        float                                       mTimeSinceLastSpawn;
        Position                                    mPosition;
        const float                                 mXOffsetAmount = 15.f;
        const float                                 mYOffsetAmount = 5.f;
};

#endif // CMAKESFMLPROJECT_PROJECTILE_CONTROLLER_H