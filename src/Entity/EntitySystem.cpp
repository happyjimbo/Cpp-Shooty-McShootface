#include <EntitySystem.h>
#include <EntityObject.h>
#include <algorithm>

// template<typename PtrType, typename>
// void EntitySystem::addObject(PtrType&& entity) {
//     if constexpr (std::is_convertible_v<PtrType, std::shared_ptr<EntityObject>>) {
//         mEntities.emplace_back(std::forward<PtrType>(entity));
//     } else if constexpr (std::is_convertible_v<PtrType, std::unique_ptr<EntityObject>>) {
//         mEntities.emplace_back(std::shared_ptr<EntityObject>(std::move(entity)));
//     }
// }

void EntitySystem::removeObject(const EntityObject& object) {
    auto found = std::find_if(mEntities.begin(), mEntities.end(),
        [&] (const std::shared_ptr<EntityObject>& p) { return p.get() == &object; });
    if (found != mEntities.end()) {
        mEntities.erase(found);
    }
}

void EntitySystem::update(const sf::Time dt) {
    for (const auto& entity : mEntities) {
        entity->update(dt);
    }
}

void EntitySystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& entity : mEntities) {

        entity->drawEntity(target, states);
    }
}

void EntitySystem::onCommand(const Command& command, sf::Time dt) {
    for (const auto& entity : mEntities) {
        entity->onCommand(command, dt);
    }
}

std::vector<std::shared_ptr<EntityObject>> EntitySystem::getEntities() const {
    return mEntities;
}