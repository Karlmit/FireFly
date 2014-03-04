#pragma once

#include "Entity.h"

#include <Thor/Particles.hpp>
#include <Thor/Animation.hpp>
#include <Thor/Vectors/PolarVector.hpp>
#include <Thor/Math/Distributions.hpp>

class Dust : public Entity
{
public:
	Dust(sf::FloatRect rect);

	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	thor::ParticleSystem mParticleSystem;
	thor::UniversalEmitter mEmitter;
};