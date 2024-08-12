#ifndef CMAKESFMLPROJECT_ENTTY_SYSTEM_H
#define CMAKESFMLPROJECT_ENTTY_SYSTEM_H

#include <unordered_set>
#include <vector>
#include <SFML/Graphics.hpp>

class EntityObject;
struct Command;

class EntitySystem {
    public:
        template<typename PtrType, typename>
        void addObject(PtrType&& entity);

        template<typename PtrType, typename>
        void removeObject(PtrType&& entity);

        void update(sf::Time dt) const;
        void lateUpdate(sf::Time dt);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void onCommand(const Command& command, sf::Time dt) const;
        std::vector<std::shared_ptr<EntityObject>>& getEntities();

    private:
        void addMarkedEntities();
        void removeMarkedEntities();

    private:
        std::vector<std::shared_ptr<EntityObject>> mEntities;
        std::vector<std::shared_ptr<EntityObject>> mEntitiesToAdd;

        std::unordered_set<EntityObject*> mEntitiesToRemove;
};

#include "EntitySystem.inl"

#endif // CMAKESFMLPROJECT_ENTTY_SYSTEM_H