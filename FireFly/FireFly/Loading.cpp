#include "Loading.h"

Loading Loading::loading;

Loading::Loading()
{
}

Loading::~Loading()
{
}

// Loads and gets the texture based on filepath
sf::Texture& Loading::getTexture(string filePath, bool smooth)
{
	loading.mTextureHolder.load(filePath, filePath);
	if (smooth)
		loading.mTextureHolder.get(filePath).setSmooth(smooth);

	return loading.mTextureHolder.get(filePath);
}

// Get soundbuffer based on SoundsEffects id
sf::SoundBuffer& Loading::getSound(string filePath)
{
	loading.mSoundBufferHolder.load(filePath, filePath);
	return loading.mSoundBufferHolder.get(filePath);
}

