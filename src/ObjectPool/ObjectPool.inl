#include "ObjectPool.h"

template<typename T>
void ObjectPool<T>::prePool(const size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        T* obj = new T();
        mPool.push_back(obj);
        mAvailable.push(obj);
    }
}

template<typename T>
template <typename... Args>
T* ObjectPool<T>::acquireObject(Args&&... args)
{
    if (mAvailable.empty())
    {
        //std::cout << "Make new" << std::endl;
        T* obj = new T();
        obj->create(std::forward<Args>(args)...);
        mPool.push_back(obj);
        return obj;
    }
    else
    {
        //std::cout << "Take from pool" << std::endl;
        T* obj = mAvailable.top();
        mAvailable.pop();
        obj->reset();
        obj->create(std::forward<Args>(args)...);
        return obj;
    }
}

template<typename T>
void ObjectPool<T>::releaseObject(T* obj)
{
    //std::cout << "release to the pool" << std::endl;
    mAvailable.push(obj);
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
