#pragma once

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SoundPool.h"
#include <SFML/Audio/SoundBuffer.hpp>

class Settings;

class SoundEffects final
{
public:
	explicit SoundEffects(const Settings& settings);
	~SoundEffects() = default;

	void play(Sounds::ID effect);
	void update();

private:
	SoundHolder mSounds {};
	SoundPool mSoundPool {10};
	const Settings& mSettings;
	std::vector<std::unique_ptr<sf::Sound>> mActiveSounds;
};
