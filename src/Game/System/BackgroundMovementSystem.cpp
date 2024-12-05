#include "BackgroundMovementSystem.h"
#include "BackgroundEntity.h"

BackgroundMovementSystem::BackgroundMovementSystem(EntitySystem<BackgroundEntity>& entitySystem) noexcept
: mEntitySystem(entitySystem)
{

}

void BackgroundMovementSystem::execute(const sf::Time& delta) const
{
    for (BackgroundEntity* background : mEntitySystem.getEntities())
    {
        const auto& [rect, bounds, scrollSpeed] = background->getBackgroundData();
        background->move(0.f, -scrollSpeed * delta.asSeconds());

        if (background->getPosition().y > bounds.y)
        {
            const float yPos = static_cast<float>(bounds.y);
            background->setPosition(0, -yPos + 1);
        }
    }
}

