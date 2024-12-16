#pragma once
#include <memory>

class GameSettings;

class Settings final
{
public:
    explicit Settings(std::shared_ptr<GameSettings> gameSettings) noexcept;
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
