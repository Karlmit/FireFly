#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "ResourceHolder.h"
using namespace std;

class Loading
{
public:
	static sf::Texture& getTexture(string filePath, bool smooth = false);
	static sf::SoundBuffer& getSound(string filePath);

private:
	static Loading loading;

private:
	Loading();
	~Loading();
	Loading(const Loading&){};
	void operator=(const Loading&);

	ResourceHolder<sf::Texture, string> mTextureHolder;
	ResourceHolder<sf::SoundBuffer, string> mSoundBufferHolder;
};