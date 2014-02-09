#pragma once

#include "Loading.h"
#include <string>
#include <SFML/Audio.hpp>

class Audio{
public:
	Audio(sf::SoundBuffer& buffer);
	~Audio();
	void playSound();
	void updateSound(sf::Vector2f position);
	sf::SoundSource::Status checkStatus();
private:
	std::string fileName;
	sf::Sound sound;
};