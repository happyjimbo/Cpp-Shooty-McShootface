#include "EntitySystem.h"

template<typename T>
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
    return entity;
}

template <typename T>
void EntitySystem<T>::removeObject(T* entity)
{
    auto it = std::find(mEntities.begin(), mEntities.end(), entity);
    if (it != mEntities.end()) {
        //delete *it;
        mObjectPool.releaseObject(*it);
        mEntities.erase(it);
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

template<typename T>
const std::vector<T*>& EntitySystem<T>::getEntities() const noexcept
{
    return mEntities;
}

template<typename T>
EntitySystem<T>::~EntitySystem() {
    mEntities.clear();
}