#include "EntitySystem.h"
#include <SFML/Graphics.hpp>

template <typename T>
void EntitySystem<T>::prePool(size_t count)
{
    mObjectPool.prePool(count);
}

template <typename T>
template <typename... Args>
T* EntitySystem<T>::createObject(Args&&... args)
{
    //T* entity = new T(std::forward<Args>(args)...);
    T* entity = mObjectPool.acquireObject(std::forward<Args>(args)...);

    mEntities.push_back(entity);
    mEntityAddressMap[entity] = mEntities.size() - 1;
    return entity;
}

template <typename T>
void EntitySystem<T>::removeObject(T* entity)
{
    // swap and pop
    auto mapEntry = mEntityAddressMap.find(entity);
    if (mapEntry != mEntityAddressMap.end())
    {
        mObjectPool.releaseObject(entity);

        size_t index = mapEntry->second;
        T* lastEntity = mEntities.back();
        std::swap(mEntities[index], mEntities.back());
        mEntityAddressMap[lastEntity] = index;

        mEntities.pop_back();
        mEntityAddressMap.erase(mapEntry);
    }
}

template <typename T>
void EntitySystem<T>::update(const sf::Time dt)
{
    for (const auto& entity : mEntities)
    {
        entity->update(dt);
    }
}

template <typename T>
const std::vector<T*>& EntitySystem<T>::getEntities() const noexcept
{
    return mEntities;
}

template <typename T>
EntitySystem<T>::~EntitySystem() {
    mEntities.clear();
}