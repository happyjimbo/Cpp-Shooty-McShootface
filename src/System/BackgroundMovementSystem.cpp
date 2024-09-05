#include "BackgroundMovementSystem.h"
#include "BackgroundEntity.h"
#include <iostream>

BackgroundMovementSystem::BackgroundMovementSystem(EntitySystem<BackgroundEntity>& entitySystem) noexcept
: mEntitySystem(entitySystem)
{

}

void BackgroundMovementSystem::execute(const sf::Time delta) const
{
    for (BackgroundEntity* background : mEntitySystem.getEntities())
    {
        const BackgroundData& data = background->getBackgroundData();
        background->move(0.f, -data.scrollSpeed * delta.asSeconds());

        if (background->getPosition().y > data.bounds.y)
        {
            const float yPos = static_cast<float>(data.bounds.y);
            background->setPosition(0, -yPos + 1);
        }
    }
}

