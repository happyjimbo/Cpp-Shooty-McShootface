#pragma once

class Performance final
{
public:
    explicit Performance() = default;
    ~Performance() = default;

    Performance(const Performance&) = delete;
    Performance& operator=(const Performance&) = delete;

    Performance(Performance&&) = delete;
    Performance& operator=(Performance&&) = delete;

    static void update(float delta);
};
