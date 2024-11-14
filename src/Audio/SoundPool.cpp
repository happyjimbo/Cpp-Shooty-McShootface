#include "SoundPool.h"

sf::Sound& SoundPool::acquire()
{
    if (poolPosition >= mPool.size())
    {
        poolPosition = 0;
    }
    return mPool[poolPosition++];
}

void SoundPool::release(sf::Sound& sound)
{
    sound.stop();
}