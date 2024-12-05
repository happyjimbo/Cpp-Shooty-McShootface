#include "CloudMovementSystem.h"

#include "CloudEntity.h"

CloudMovementSystem::CloudMovementSystem(EntitySystem<CloudEntity>& entitySystem) noexcept
: mEntitySystem(entitySystem)
{

}

void CloudMovementSystem::execute(const sf::Time& delta) const
{
    for (CloudEntity* cloud : mEntitySystem.getEntities())
    {
        const auto& cloudData = cloud->getCloudData();
        const auto& [cloudRect, scrollSpeed, scrollSpeedOffset] = cloudData;

        cloud->move(0.f, -(scrollSpeed * scrollSpeedOffset) * delta.asSeconds());

        if (cloud->getPosition().y > cloudRect.getSize().y)
        {
            cloud->setPosition(cloudData.generateRandomXpos(), -cloudRect.getSize().y+1);
        }
    }
}

