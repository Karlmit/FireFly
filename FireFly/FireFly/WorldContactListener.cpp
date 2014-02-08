#include "WorldContactListener.h"
#include <iostream>
using namespace std;

void WorldContactListener::BeginContact(b2Contact *contact)
{
	if (contact->GetFixtureA()->GetBody()->GetLinearVelocity().Length() > 10.f)
		cout << contact->GetFixtureA()->GetBody()->GetLinearVelocity().Length() << " ";

	if (contact->GetFixtureB()->GetBody()->GetLinearVelocity().Length() > 10.f)
		cout << contact->GetFixtureB()->GetBody()->GetLinearVelocity().Length() << " ";
}
 
void WorldContactListener::EndContact(b2Contact *contact)
{

}

void WorldContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
	 
}

void WorldContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{

}