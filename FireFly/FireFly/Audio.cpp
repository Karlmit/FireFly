#include "Audio.h"

Audio::Audio(sf::SoundBuffer& buffer, bool global)
	: mSound(buffer)
{	
	mSound.setVolume(100);
	mSound.setMinDistance(500.f);
	mSound.setAttenuation(2.f);
	mSound.setRelativeToListener(global);
}

Audio::~Audio()
{
}

void Audio::play()
{
	mSound.play();
	
}

void Audio::setPosition(sf::Vector2f position)
{
	mSound.setPosition (position.x, 1, position.y);
}

sf::Sound::Status Audio::getStatus()
{
	return mSound.getStatus();
}

sf::Sound* Audio::getSound()
{
	return &mSound;
}