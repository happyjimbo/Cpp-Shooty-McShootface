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

    static void update(float delta);
};
