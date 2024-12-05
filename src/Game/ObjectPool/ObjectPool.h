#pragma once

#include <vector>
#include <stack>

template<typename T>
class ObjectPool final
{
public:
    explicit ObjectPool(size_t initialSize = 0);
    ~ObjectPool() noexcept = default;

    void prePool(size_t count);

    template <typename... Args>
    T& acquireObject(Args&&... args);

    void releaseObject(T& obj);

private:
    std::vector<size_t> mAvailable;
    std::vector<T> mPool;
};

#include "ObjectPool.inl"