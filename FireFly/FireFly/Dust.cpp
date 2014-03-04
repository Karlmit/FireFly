#include "Dust.h"
#include <iostream>


Dust::Dust(sf::FloatRect rect)
	: mParticleSystem()
	, mEmitter()
{
	// Set up particle system //
	// Create emitter
	mEmitter.setEmissionRate(50);
	mEmitter.setParticleLifetime(sf::seconds(4.f));
	mEmitter.setParticleScale(sf::Vector2f(0.2f, 0.2f));
	sf::Color color(165, 120, 42, 80);
	mEmitter.setParticleColor(color);

	sf::Vector2f center(rect.left + rect.width/2, rect.top + rect.height/2);
	sf::Vector2f halfsize(rect.width/2, rect.height/2);
	mEmitter.setParticlePosition(thor::Distributions::rect(center, halfsize));

	mEmitter.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(0, 15.f), 70));


	

	// Create particle system, add reference to emitter
	mParticleSystem.setTexture(Loading::getTexture("particle.png"));
	mParticleSystem.addEmitter(thor::refEmitter(mEmitter));

	// fade in/out animations
	thor::FadeAnimation fader(0.09f, 0.1f);

	// Add particle affectors
	//mParticleSystem.addAffector( thor::AnimationAffector(colorizer) );
	mParticleSystem.addAffector( thor::AnimationAffector(fader) );
	//mParticleSystem.addAffector( thor::TorqueAffector(100.f) );
	//mParticleSystem.addAffector( thor::ForceAffector(sf::Vector2f(0.f, 20))  );
}

void Dust::updateEntity(sf::Time dt)
{
	// Update particle system
	mParticleSystem.update(dt);
}

void Dust::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw particles
	target.draw(mParticleSystem);
}

