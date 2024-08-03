#ifndef CMAKESFMLPROJECT_PROJECTILE_CONTROLLER_H
#define CMAKESFMLPROJECT_PROJECTILE_CONTROLLER_H

#include "projectile.h"

class ProjectileController : public SceneNode {

    private:
        enum Position {
            Left,
            Right
        };

    public:
        void                                        spawn(Projectile::Type type);

        ProjectileController(const TextureHolder& texture);

        void                                        tick(sf::Time delta, sf::Vector2f position, float speed);
        virtual unsigned int	                    getCategory() const;
        std::vector<Projectile*>                    getProjectiles() const;
        void                                        destroy(const Projectile& projectile);

    private:
        void                                        accelerate(float speed) const;

    private:
        std::vector<Projectile*>                    mProjectiles;
        const TextureHolder&                        mTexture;
        sf::Vector2f                                mSpawnPosition;
        float                                       mTimeSinceLastSpawn;
        Position                                    mPosition;
        const float                                 mXOffsetAmount = 15.f;
        const float                                 mYOffsetAmount = 5.f;
};

#endif // CMAKESFMLPROJECT_PROJECTILE_CONTROLLER_H