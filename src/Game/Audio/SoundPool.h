#pragma once

#include <SFML/Audio/Sound.hpp>
#include <queue>

class SoundPool
{
public:
    explicit SoundPool() = default;
    ~SoundPool() = default;

    explicit SoundPool(const SoundPool&) = delete;
    SoundPool& operator=(const SoundPool&) = delete;

    explicit SoundPool(SoundPool&&) = delete;
    SoundPool& operator=(SoundPool&&) = delete;

    sf::Sound& acquire();
    static void release(sf::Sound& sound);

    static constexpr size_t POOL_SIZE = 10;

private:
    size_t poolPosition {0};
    std::array<sf::Sound, POOL_SIZE> mPool;
};
