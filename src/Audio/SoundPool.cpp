#include "SoundPool.h"

SoundPool::SoundPool(const std::size_t poolSize)
{
    for (std::size_t i = 0; i < poolSize; ++i)
    {
        mPool.emplace(new sf::Sound());
    }
}

std::unique_ptr<sf::Sound> SoundPool::acquire()
{
    if (!mPool.empty())
    {
        std::unique_ptr<sf::Sound> sound = std::move(mPool.front());
        mPool.pop();
        return sound;
    }
    return nullptr;
}

void SoundPool::release(std::unique_ptr<sf::Sound> sound)
{
    sound->stop();
    mPool.push(std::move(sound));
}