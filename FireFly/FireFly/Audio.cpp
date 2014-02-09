#include "Audio.h"

Audio::Audio(sf::SoundBuffer& buffer)
{
	sound.setBuffer(buffer);
}

Audio::~Audio()
{

}

void Audio::playSound()
{
	sound.play();
}

void Audio::updateSound(sf::Vector2f position)
{
	sound.setPosition (position.x, position.y, 1);
}