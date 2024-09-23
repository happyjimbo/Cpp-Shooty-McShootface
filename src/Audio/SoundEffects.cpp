#include "SoundEffects.h"
#include "MediaFiles.h"
#include "ResourceHolder.h"
#include "Settings.h"

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>


SoundEffects::SoundEffects(const Settings& settings)
: mSettings(settings)
{
	mSounds.load(Sounds::PlayerGunfire, AudioFiles::PlayerGunfire);
	mSounds.load(Sounds::EnemyGunfire, AudioFiles::EnemyGunfire);
	mSounds.load(Sounds::Explosion1, AudioFiles::Explosion1);
	mSounds.load(Sounds::Explosion2, AudioFiles::Explosion2);
}

void SoundEffects::play(const Sounds::ID effect)
{
	if (!mSettings.isMuted())
	{
		std::unique_ptr<sf::Sound> sound = mSoundPool.acquire();
		if (sound)
		{
			sound->setBuffer(mSounds.get(effect));
			sound->play();
			mActiveSounds.push_back(std::move(sound));
		}
	}
}

void SoundEffects::update()
{
	for (auto it = mActiveSounds.begin(); it != mActiveSounds.end();)
	{
		if ((*it) && (*it)->getStatus() == sf::SoundSource::Stopped)
		{
			mSoundPool.release(std::move(*it));
			it = mActiveSounds.erase(it);
		}
		else
		{
			++it;
		}
	}
}