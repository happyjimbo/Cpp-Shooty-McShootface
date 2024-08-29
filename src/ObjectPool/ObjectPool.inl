#include "ObjectPool.h"

template<typename T>
void ObjectPool<T>::prePool(const size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        T* obj = new T();
        mPool.push_back(obj);
    }
}

template<typename T>
template <typename... Args>
T* ObjectPool<T>::acquireObject(Args&&... args)
{
    if (mPool.empty())
    {
        //std::cout << "Make new" << std::endl;
        T* obj = new T();
        obj->create(std::forward<Args>(args)...);
        return obj;
    }
    else
    {
        //std::cout << "Take from pool" << std::endl;
        T* obj = mPool.back();
        mPool.pop_back();
        obj->reset();
        obj->create(std::forward<Args>(args)...);
        return obj;
    }
}

template<typename T>
void ObjectPool<T>::releaseObject(T* obj)
{
    mPool.push_back(obj);
}

template<typename T>
ObjectPool<T>::~ObjectPool() noexcept
{
    for (const T* obj : mPool)
    {
        delete obj;
    }
    mPool.clear();
}
