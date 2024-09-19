#include "SoundEffects.h"
#include "MediaFiles.h"
#include "ResourceHolder.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

SoundEffects::SoundEffects()
{
	mSounds.load(Sounds::PlayerGunfire, AudioFiles::PlayerGunfire);
	mSounds.load(Sounds::EnemyGunfire, AudioFiles::EnemyGunfire);
	mSounds.load(Sounds::Explosion1, AudioFiles::Explosion1);
	mSounds.load(Sounds::Explosion2, AudioFiles::Explosion2);
}

void SoundEffects::play(const Sounds::ID effect)
{
	sf::Sound* sound = mSoundPool.acquire();
	if (sound)
	{
		sound->setBuffer(mSounds.get(effect));
		sound->play();
		mActiveSounds.push_back(sound);
	}
}

void SoundEffects::update()
{
	std::erase_if(mActiveSounds, [this](sf::Sound* sound)
	{
		if (sound->getStatus() == sf::SoundSource::Stopped)
		{
			mSoundPool.release(sound);
			return true;
		}
		return false;
	});
}

SoundEffects::~SoundEffects()
{
	// Ensure that all active sounds are properly released or deleted
	for (sf::Sound* sound : mActiveSounds)
	{
		mSoundPool.release(sound);
	}
	mActiveSounds.clear();
}