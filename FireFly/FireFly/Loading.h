#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "ResourceHolder.h"
#include "ResourceID.h"


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
	const sf::Texture& getTexture(TexturesID id) const;
	sf::Texture& getTexture(TexturesID id);

	// Get soundbuffer based on SoundsEffects id
	 const sf::SoundBuffer& getSound(SoundEffectsID id) const;
	 sf::SoundBuffer& getSound(SoundEffectsID id);

private:
	Loading();
	~Loading();
	Loading(const Loading&){};
	void operator=(const Loading&);

	ResourceHolder<sf::Texture, TexturesID> mTextureHolder;
	ResourceHolder<sf::SoundBuffer, SoundEffectsID> mSoundBufferHolder;

private:
	void loadTextureSmooth(TexturesID textureId, const std::string& filename);
};