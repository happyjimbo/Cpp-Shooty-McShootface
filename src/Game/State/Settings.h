#pragma once
#include <memory>

class Settings final
{
public:
    explicit Settings() noexcept;
    ~Settings() noexcept;

    explicit Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    explicit Settings(Settings&&) = delete;
    Settings& operator=(Settings&&) = delete;

    void draw() const;
    bool isPaused() const;
    bool isMuted() const;

private:
    struct Impl;
    std::unique_ptr<Impl> mImpl;
};
