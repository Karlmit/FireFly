#include "AudioEntity.h"

AudioEntity::AudioEntity(Audio audio)
	:mAudio(audio)
{
	mAudio.play();
}

void AudioEntity::updateEntity(sf::Time dt)
{
	if (mAudio.getStatus() == sf::Sound::Status::Stopped)
		killEntity();
}

void AudioEntity::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{

}