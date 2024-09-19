#include "SoundPool.h"

SoundPool::SoundPool(const std::size_t poolSize)
{
    for (std::size_t i = 0; i < poolSize; ++i)
    {
        mPool.emplace(new sf::Sound());
    }
}

sf::Sound* SoundPool::acquire()
{
    if (!mPool.empty())
    {
        sf::Sound* sound = mPool.front();
        mPool.pop();
        return sound;
    }
    return nullptr;
}

void SoundPool::release(sf::Sound* sound)
{
    sound->stop();
    mPool.push(sound);
}

SoundPool::~SoundPool()
{
    while (!mPool.empty())
    {
        delete mPool.front();
        mPool.pop();
    }
}