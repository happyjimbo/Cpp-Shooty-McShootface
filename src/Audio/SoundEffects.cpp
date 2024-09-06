#include "SoundEffects.h"
#include "MediaFiles.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "ResourceHolder.h"

SoundEffects::SoundEffects()
{
    mSounds.load(Sounds::PlayerGunfire, AudioFiles::PlayerGunfire);
    mSounds.load(Sounds::EnemyGunfire, AudioFiles::EnemyGunfire);
    mSounds.load(Sounds::Explosion1, AudioFiles::Explosion1);
    mSounds.load(Sounds::Explosion2, AudioFiles::Explosion2);
}

void SoundEffects::play(const Sounds::ID effect)
{
    mSound.setBuffer(mSounds.get(effect));
    mSound.play();
}
