#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "ResourceHolder.h"

namespace Textures
{
	enum ID
	{
		Zid,
		Moth,
	};
}

namespace SoundEffects
{
	enum ID
	{
		Fly,
		Moth,
	};
}

class Loading
{
public:
	static Loading &getLoading();
private:
	static Loading loading;

public:
	// Load res for level 0
	void loadLevel0();

	// Get texture based on Textures id
	const sf::Texture& GetTexture(Textures::ID id) const;
	sf::Texture& GetTexture(Textures::ID id);

	// Get soundbuffer based on SoundsEffects id
	 const sf::SoundBuffer& GetSound(SoundEffects::ID id) const;
	 sf::SoundBuffer& GetSound(SoundEffects::ID id);

private:
	Loading();
	~Loading();
	void operator=(const Loading &loading);
	

	//sf::SoundBuffer mothBuffer;
	//sf::SoundBuffer fly;

	ResourceHolder<sf::Texture, Textures::ID> mTextureHolder;

	ResourceHolder<sf::SoundBuffer, SoundEffects::ID> mSoundBufferHolder;
};