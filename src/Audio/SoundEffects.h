#pragma once

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SoundPool.h"
#include <SFML/Audio/SoundBuffer.hpp>

class SoundEffects final
{
public:
	explicit SoundEffects();
	~SoundEffects();

	void play(Sounds::ID effect);
	void update();

private:
	SoundHolder mSounds {};
	SoundPool mSoundPool {10};
	std::vector<sf::Sound*> mActiveSounds;
};
