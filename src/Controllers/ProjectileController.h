#ifndef CMAKESFMLPROJECT_PROJECTILE_CONTROLLER_H
#define CMAKESFMLPROJECT_PROJECTILE_CONTROLLER_H

#include <unordered_set>
#include <vector>

#include <Entity/ProjectileEntity.h>
#include <Entity/EntitySystem.h>

class ProjectileController final {

    private:
        enum Position {
            Left,
            Right
        };

    public:
        ProjectileController(EntitySystem<ProjectileEntity>& entitySystem, const TextureHolder& texture, sf::FloatRect worldBounds);
        void spawn(ProjectileEntity::Type type, sf::Vector2f spawnPosition);
        void tick(sf::Time delta, float speed);
        void removeEntity(ProjectileEntity* entity) const;
        const std::vector<ProjectileEntity*>& getProjectiles() const;

    private:
        void accelerate(sf::Time delta, float speed) const;
        void checkBounds() const;

    private:
        const TextureHolder& mTexture;
        const sf::FloatRect mWorldBounds;
        float mTimeSinceLastSpawn;

        Position mPosition;
        const float mXOffsetAmount = 15.f;
        const float  mYOffsetAmount = 5.f;


        std::vector<ProjectileEntity*>  mEntities;
        EntitySystem<ProjectileEntity>& mEntitySystem;
};

#endif // CMAKESFMLPROJECT_PROJECTILE_CONTROLLER_H