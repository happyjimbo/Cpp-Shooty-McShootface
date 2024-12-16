#pragma once

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SoundPool.h"
#include <SFML/Audio/SoundBuffer.hpp>

struct SoundSettings;

class SoundEffects final
{
public:
	explicit SoundEffects(const SoundSettings& settings);
	~SoundEffects() = default;

	void play(Sounds::ID effect);
	void update();

private:
	SoundHolder mSounds {};
	SoundPool mSoundPool;
	const SoundSettings& mSettings;
	size_t activeSoundPosition {0};

	std::array<sf::Sound*, SoundPool::POOL_SIZE> mActiveSounds = {nullptr};
};
