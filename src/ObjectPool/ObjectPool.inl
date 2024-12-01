#include <assert.h>

#include "ObjectPool.h"

template<typename T>
void ObjectPool<T>::prePool(const size_t count)
{
    mPool.reserve(count);

    for (size_t i = 0; i < count; i++)
    {
        T* obj = new T();
        mPool.push_back(obj);
        mAvailable.push_back(obj);
    }
}

template<typename T>
template <typename... Args>
T* ObjectPool<T>::acquireObject(Args&&... args)
{
    if (mAvailable.empty())
    {
        T* obj = new T();
        obj->create(std::forward<Args>(args)...);
        mPool.push_back(obj);
        return obj;
    }
    else
    {
        T* obj = mAvailable.back();
        mAvailable.pop_back();

        obj->reset();
        obj->create(std::forward<Args>(args)...);
        return obj;
    }
}

template<typename T>
void ObjectPool<T>::releaseObject(T* obj)
{
    assert(std::find(mPool.begin(), mPool.end(), obj) != mPool.end() && "Object not found in the pool");
    mAvailable.push_back(obj);
}

template<typename T>
ObjectPool<T>::~ObjectPool() noexcept
{
    for (const T* obj : mPool)
    {
        delete obj;
    }
    mPool.clear();
    mAvailable.clear();
}