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
        const CloudData& cloudData = cloud->getCloudData();

        cloud->move(0.f, -(cloudData.scrollSpeed * cloudData.scrollSpeedOffset) * delta.asSeconds());

        if (cloud->getPosition().y > cloudData.cloudRect.getSize().y)
        {
            cloud->setPosition(cloudData.generateRandomXpos(), -cloudData.cloudRect.getSize().y+1);
        }
    }
}

