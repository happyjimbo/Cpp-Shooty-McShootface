#include <EntitySystem.h>
#include <EntityObject.h>
#include "Command.h"

void EntitySystem::update(const sf::Time dt) const
{
    for (const auto& entity : mEntities)
    {
        entity->update(dt);
    }
}

void EntitySystem::lateUpdate(const sf::Time) {
    removeMarkedEntities();
    addMarkedEntities();
}

void EntitySystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& entity : mEntities)
    {
        entity->draw(target, states);
    }
}

void EntitySystem::onCommand(const Command& command, const sf::Time dt) const
{
    for (const auto& entity : mEntities)
    {
        if (command.category & entity->getCategory()) {
            command.entityAction(*entity, dt);
        }
    }
}

std::vector<std::shared_ptr<EntityObject>>& EntitySystem::getEntities()
{
    return mEntities;
}

void EntitySystem::addMarkedEntities() {
    for (auto& entity : mEntitiesToAdd) {
        mEntities.emplace_back(std::move(entity));
    }
    mEntitiesToAdd.clear();
}

void EntitySystem::removeMarkedEntities()
{
    mEntities.erase( std::remove_if(mEntities.begin(), mEntities.end(),
        [this](const std::shared_ptr<EntityObject>& entity) {
            return entity == nullptr || mEntitiesToRemove.count(entity.get()) > 0;
        }), mEntities.end());

    mEntitiesToRemove.clear();
}