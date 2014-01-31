#pragma once
#include "Entity.h"

class Mal : public Entity
{
public:
	Mal();
	~Mal();
	void updateEntity(sf::Time dt);
	void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
private:
};

