#pragma once

#include <vector>

template<typename T>
class ObjectPool final
{
public:
    ~ObjectPool() noexcept;

    template <typename... Args>
    T* acquireObject(Args&&... args);
    void releaseObject(T* obj);

private:
    std::vector<T*> mPool;
};

#include "ObjectPool.inl"