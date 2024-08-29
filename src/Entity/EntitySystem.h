#pragma once

#include <unordered_set>
#include <vector>
#include <SFML/Graphics.hpp>

#include "ObjectPool.h"

struct Command;

template<typename T>
class EntitySystem final {
public:

    explicit EntitySystem() = default;
    ~EntitySystem();

    void prePool(size_t count);

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
    ObjectPool<T> mObjectPool;
};

#include "EntitySystem.inl"