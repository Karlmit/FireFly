#pragma once

#include "Entity.h"
#include "Audio.h"

class AudioEntity : public Entity
{
public:
	AudioEntity(Audio audio);

	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Audio mAudio;
};