#include "Loading.h"

Loading Loading::loading;
Loading &Loading::getLoading()
{
	return loading;
}

Loading::Loading(){}

Loading::~Loading(){}

//
// Get texture based on Textures id
//
const sf::Texture& Loading::getTexture(TexturesID id) const
{
	return mTextureHolder.get(id);
}


// Get texture based on Textures id
sf::Texture& Loading::getTexture(TexturesID id)
{
	return mTextureHolder.get(id);
}

// Get soundbuffer based on SoundsEffects id
const sf::SoundBuffer& Loading::getSound(SoundEffectsID id) const
{
	return mSoundBufferHolder.get(id);
}

// Get soundbuffer based on SoundsEffects id
sf::SoundBuffer& Loading::getSound(SoundEffectsID id)
{
	return mSoundBufferHolder.get(id);
}


// Loads the resources for level 0
void Loading::loadLevel0()
{
	// Sounds
	mSoundBufferHolder.load(SoundEffectsID::Moth, "Resources/canary.wav");

	// Textures
	mTextureHolder.load(TexturesID::Zid, "Resources/zid.png");
	mTextureHolder.load(TexturesID::Moth, "Resources/mal.png");

	mTextureHolder.load(TexturesID::ROOM1_Background, "Resources/Room 1/RUM_1.png");
	mTextureHolder.load(TexturesID::ROOM1_Foreground, "Resources/Room 1/Forgrund.png");
	mTextureHolder.load(TexturesID::ROOM1_Coat1, "Resources/Room 1/Coat 1.png");
	mTextureHolder.load(TexturesID::ROOM1_Coat5, "Resources/Room 1/Coat 5.png");
	mTextureHolder.load(TexturesID::ROOM1_JAR, "Resources/Room 1/Firefly_burk.png");
}