#include <EntitySystem.h>
#include <EntityObject.h>

void EntitySystem::update(const sf::Time dt) const
{
    for (const auto& entity : mEntities)
    {
        entity->update(dt);
    }
}

void EntitySystem::lateUpdate(const sf::Time) {
    if (!mEntitiesToRemove.empty())
    {
        removeMarkedEntities();
    }
}

void EntitySystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& entity : mEntities)
    {
        entity->drawEntity(target, states);
    }
}

void EntitySystem::onCommand(const Command& command, const sf::Time dt) const
{
    for (const auto& entity : mEntities)
    {
        entity->onCommand(command, dt);
    }
}

std::vector<std::shared_ptr<EntityObject>> EntitySystem::getEntities() const
{
    return mEntities;
}

void EntitySystem::removeMarkedEntities()
{
    mEntities.erase(
        std::remove_if(mEntities.begin(), mEntities.end(),
                       [this](const std::shared_ptr<EntityObject>& entity) {
                           return entity == nullptr || mEntitiesToRemove.count(entity.get()) > 0;
                       }),
        mEntities.end());

    mEntitiesToRemove.clear();
}