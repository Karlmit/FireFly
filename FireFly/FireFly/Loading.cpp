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
	string res = "Resources/";
	res.append(filePath);

	loading.mTextureHolder.load(res, res);
	if (smooth)
		loading.mTextureHolder.get(res).setSmooth(smooth);

	return loading.mTextureHolder.get(res);
}

// Get soundbuffer based on SoundsEffects id
sf::SoundBuffer& Loading::getSound(string filePath)
{
	string res = "Resources/";
	res.append(filePath);

	loading.mSoundBufferHolder.load(res, res);
	return loading.mSoundBufferHolder.get(res);
}

