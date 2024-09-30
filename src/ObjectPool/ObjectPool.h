#pragma once

#include <vector>

template<typename T>
class ObjectPool final
{
public:
    ObjectPool() = default;
    ~ObjectPool() noexcept;

    void prePool(size_t count);

    template <typename... Args>
    T* acquireObject(Args&&... args);

    void releaseObject(T* obj);

private:
    std::stack<T*> mAvailable;
    std::vector<T*> mPool;
};

#include "ObjectPool.inl"