#include <cassert>
#include <iostream>

#include "ObjectPool.h"

template <typename T>
ObjectPool<T>::ObjectPool(const size_t initialSize)
{
    prePool(initialSize);
}

template <typename T>
void ObjectPool<T>::prePool(const size_t count)
{
    const size_t currentSize = mPool.size();
    mPool.resize(currentSize + count);
    for (size_t i = currentSize; i < mPool.size(); ++i)
    {
        mAvailable.push_back(i);
    }
}

template <typename T>
template <typename... Args>
T& ObjectPool<T>::acquireObject(Args&&... args)
{
    if (mAvailable.empty())
    {
        prePool(mPool.size() == 0 ? 1 : mPool.size());
    }

    size_t index = mAvailable.back();
    mAvailable.pop_back();

    T& obj = mPool[index];
    obj.create(std::forward<Args>(args)...);

    return obj;
}

template <typename T>
void ObjectPool<T>::releaseObject(T& obj)
{
    size_t index = &obj - mPool.data();
    assert(index < mPool.size() && "Object not managed by this pool");

    mAvailable.push_back(index);
}