#include "SoundEffects.h"
#include "MediaFiles.h"
#include "ResourceHolder.h"

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include "SoundSettings.h"


SoundEffects::SoundEffects(const SoundSettings& settings)
: mSettings(settings)
{
	mSounds.load(Sounds::PlayerGunfire, AudioFiles::PlayerGunfire);
	mSounds.load(Sounds::EnemyGunfire, AudioFiles::EnemyGunfire);
	mSounds.load(Sounds::Explosion1, AudioFiles::Explosion1);
	mSounds.load(Sounds::Explosion2, AudioFiles::Explosion2);
}

void SoundEffects::play(const Sounds::ID effect)
{
	if (!mSettings.isMuted)
	{
		sf::Sound& sound = mSoundPool.acquire();
		sound.setBuffer(mSounds.get(effect));
		sound.play();
		if (activeSoundPosition >= mActiveSounds.size())
		{
			activeSoundPosition = 0;
		}
		mActiveSounds[activeSoundPosition++] = &sound;
	}
}

void SoundEffects::update()
{
	for (auto& sound : mActiveSounds)
	{
		if (sound && sound->getStatus() == sf::SoundSource::Stopped)
		{
			mSoundPool.release(*sound);
			sound = nullptr;
		}
	}
}