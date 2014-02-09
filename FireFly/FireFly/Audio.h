#pragma once

#include "Loading.h"
#include <string>
#include <SFML/Audio.hpp>

class Audio
{
public:
	Audio(sf::SoundBuffer& buffer, bool global = false);
	~Audio();
	void play();
	void setPosition(sf::Vector2f position);
	sf::Sound::Status getStatus();
	sf::Sound* getSound();

private:
	sf::Sound mSound;
};