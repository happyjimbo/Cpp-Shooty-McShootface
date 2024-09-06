#pragma once
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include <SFML/Audio/SoundBuffer.hpp> // needed to enable the forward declaration
#include <SFML/Audio/Sound.hpp>


class SoundEffects final
{
public:
	explicit SoundEffects();
    void play(Sounds::ID effect);

private:
	SoundHolder mSounds {};
	sf::Sound mSound {};
};



	/*public:
									SoundPlayer();

		void						play(SoundEffect::ID effect);
		void						play(SoundEffect::ID effect, sf::Vector2f position);

		void						removeStoppedSounds();
		void						setListenerPosition(sf::Vector2f position);
		sf::Vector2f				getListenerPosition() const;


	private:
		SoundBufferHolder			mSoundBuffers;
		std::list<sf::Sound>		mSounds;*/