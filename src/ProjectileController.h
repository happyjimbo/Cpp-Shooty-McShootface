#ifndef CMAKESFMLPROJECT_PROJECTILE_CONTROLLER_H
#define CMAKESFMLPROJECT_PROJECTILE_CONTROLLER_H

#include "Projectile.h"

class ProjectileController final : public SceneNode {

    private:
        enum Position {
            Left,
            Right
        };

    public:
                                                    ProjectileController(const TextureHolder& texture, const sf::FloatRect worldBounds);
        void                                        spawn(Projectile::Type type);
        void                                        tick(const sf::Time delta, const sf::Vector2f position, const float speed);
        virtual unsigned int	                    getCategory() const;
        std::vector<Projectile*>                    getProjectiles() const;
        void                                        destroy(const Projectile& projectile);

    private:
        void accelerate(float speed) const;
        void checkBounds();

    private:
        std::vector<Projectile*>                    mProjectiles;
        const TextureHolder&                        mTexture;
        const sf::FloatRect                         mWorldBounds;
        sf::Vector2f                                mSpawnPosition;
        float                                       mTimeSinceLastSpawn;
        Position                                    mPosition;
        const float                                 mXOffsetAmount = 15.f;
        const float                                 mYOffsetAmount = 5.f;
};

#endif // CMAKESFMLPROJECT_PROJECTILE_CONTROLLER_H