#include "Audio.h"

Audio::Audio(SoundEffectsID buffer)
{
	sound.setBuffer(Loading::getLoading().getSound(buffer));
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