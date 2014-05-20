#include "Audio.h"

Audio::Audio(sf::SoundBuffer& buffer, bool global) //Creates a sound with its own buffer.
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

void Audio::play() //Lets others play the sound with a function.
{
	mSound.play();
}

void Audio::pause()
{
	mSound.pause();
}

void Audio::stop()
{
	mSound.stop();
}


void Audio::setPosition(sf::Vector2f position) //Places the sound so it is heard by the listener from that point.
{
	mSound.setPosition (position.x, 1, position.y);
}

sf::Sound::Status Audio::getStatus() //Lets others know in what state the sound is in. Should never return "paused" for now.
{
	return mSound.getStatus();
}

sf::Sound* Audio::getSound()
{
	return &mSound;
}

void Audio::setLoop(bool statement)
{
	mSound.setLoop(statement);
}
