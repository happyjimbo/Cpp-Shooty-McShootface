#pragma once

#include <unordered_set>
#include <vector>
#include <SFML/Graphics.hpp>

class EntityObject;
struct Command;

template<typename T>
class EntitySystem final {
public:
    ~EntitySystem();
    template <typename... Args>
    T* createObject(Args&&... args);

    void removeObject(T* entity);
    void update(sf::Time dt);

    // void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void onCommand(const Command& command, sf::Time dt) const;
    const std::vector<T*>& getEntities() const noexcept;

private:
    // mEntites should probably be a list due to removing
    // entities from any part of it
    std::vector<T*> mEntities;
    std::vector<T*> mEntitiesToAdd;
    std::unordered_set<T*> mEntitiesToRemove;
};

#include "EntitySystem.inl"