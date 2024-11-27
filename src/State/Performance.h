#pragma once
#include <deque>

class Performance final
{
public:
    explicit Performance() = default;
    ~Performance() = default;

    Performance(Performance&) = delete;
    Performance& operator=(Performance&) = delete;

    Performance(Performance&&) = delete;
    Performance& operator=(Performance&&) = delete;

    void update(float delta);
    void update(float delta) const;
};
