#pragma once

#include <SFML/Audio/Sound.hpp>
#include <queue>

class SoundPool
{
public:
    explicit SoundPool(std::size_t poolSize);
    ~SoundPool();

    explicit SoundPool(SoundPool&) = delete;
    SoundPool& operator=(SoundPool&) = delete;

    explicit SoundPool(SoundPool&&) = delete;
    SoundPool& operator=(SoundPool&&) = delete;

    sf::Sound* acquire();
    void release(sf::Sound* sound);

private:
    std::queue<sf::Sound*> mPool;
};