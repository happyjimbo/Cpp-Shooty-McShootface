#pragma once

#include <unordered_set>
#include <vector>

#include "ObjectPool.h"

namespace sf { class Time; }

struct Command;

template<typename T>
class EntitySystem final {
public:

    explicit EntitySystem() = default;
    ~EntitySystem();

    EntitySystem(EntitySystem&) = delete;
    EntitySystem& operator=(EntitySystem&) = delete;

    EntitySystem(EntitySystem&&) = delete;
    EntitySystem& operator=(EntitySystem&&) = delete;

    void prePool(size_t count);

    template <typename... Args>
    T* createObject(Args&&... args);

    void removeObject(T* entity);
    void update(sf::Time dt);

    const std::vector<T*>& getEntities() const noexcept;

private:
    std::vector<T*> mEntities;
    std::unordered_map<T*, size_t> mEntityAddressMap;
    ObjectPool<T> mObjectPool;
};

#include "EntitySystem.inl"