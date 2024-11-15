#pragma once

#include <vector>

#include "ObjectPool.h"

namespace sf { class Time; }

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

    const std::vector<T*>& getEntities() const noexcept;

private:
    // mEntites should probably be a list due to removing
    // entities from any part of it
    std::vector<T*> mEntities;
    ObjectPool<T> mObjectPool;
};

#include "EntitySystem.inl"