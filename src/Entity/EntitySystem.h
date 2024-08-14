#ifndef CMAKESFMLPROJECT_ENTTY_SYSTEM_H
#define CMAKESFMLPROJECT_ENTTY_SYSTEM_H

#include <unordered_set>
#include <vector>
#include <SFML/Graphics.hpp>

class EntityObject;
struct Command;

template<typename T>
class EntitySystem {
    public:

        template <typename... Args>
        T* createObject(Args&&... args);

        void removeObject(T* entity);
        void update(sf::Time dt);

        // void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void onCommand(const Command& command, sf::Time dt) const;
        const std::vector<T*>& getEntities() const;

    private:
        // mEntites should probably be a list due to removing
        // entities from any part of it
        std::vector<T*> mEntities;
        std::vector<T*> mEntitiesToAdd;
        std::unordered_set<T*> mEntitiesToRemove;
};

#include "EntitySystem.inl"

#endif // CMAKESFMLPROJECT_ENTTY_SYSTEM_H