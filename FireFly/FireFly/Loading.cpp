#include "Loading.h"

Loading Loading::loading;
Loading &Loading::getLoading()
{
	return loading;
}

Loading::Loading()
{
}

Loading::~Loading()
{
	
}



const sf::Texture& Loading::GetTexture(Textures::ID id) const
{
	return mTextureHolder.get(id);
}

sf::Texture& Loading::GetTexture(Textures::ID id)
{
	return mTextureHolder.get(id);
}

const sf::SoundBuffer& Loading::GetSound(SoundEffects::ID id) const
{
	return mSoundBufferHolder.get(id);
}

sf::SoundBuffer& Loading::GetSound(SoundEffects::ID id)
{
	return mSoundBufferHolder.get(id);
}





void Loading::loadLevel0()
{
	// Sounds
	mSoundBufferHolder.load(SoundEffects::Moth, "Resources/canary.wav");

	// Textures
	mTextureHolder.load(Textures::Zid, "Resources/zid.png");
	mTextureHolder.load(Textures::Moth, "Resources/mal.png");

	mTextureHolder.load(Textures::Background_Room1, "Resources/RUM_1.png");
}