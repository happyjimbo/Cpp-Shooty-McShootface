#include "ExplosionAnimationSystem.h"
#include "ExplosionEntity.h"
#include <SFML/System/Time.hpp>

ExplosionAnimationSystem::ExplosionAnimationSystem(EntitySystem<ExplosionEntity>& entitySystem) noexcept
: mEntitySystem(entitySystem)
{
}

void ExplosionAnimationSystem::execute(const sf::Time delta) const
{
    for (const auto& entity : mEntitySystem.getEntities())
    {
        AnimationData& explosionData = entity->getExplosionData();;
        explosionData.updateTimeSinceLastFrame(delta.asSeconds());

        if (explosionData.canIncreaseFrame(mDelay))
        {
            explosionData.nextFrame();

            const auto explosionRect = explosionData.getAnimationRect();
            entity->setTextureRect(explosionRect);
        }
        else if (explosionData.hasAnimationEnded())
        {
            mEntitySystem.removeObject(entity);
        }
    }

}
