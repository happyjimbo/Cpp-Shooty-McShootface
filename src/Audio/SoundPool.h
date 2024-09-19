#pragma once

#include <SFML/Audio/Sound.hpp>
#include <queue>

class SoundPool
{
public:
    explicit SoundPool(std::size_t poolSize);
    ~SoundPool() = default;

    explicit SoundPool(SoundPool&) = delete;
    SoundPool& operator=(SoundPool&) = delete;

    explicit SoundPool(SoundPool&&) = delete;
    SoundPool& operator=(SoundPool&&) = delete;

    std::unique_ptr<sf::Sound> acquire();
    void release(std::unique_ptr<sf::Sound> sound);

private:
    std::queue<std::unique_ptr<sf::Sound>> mPool;
};
