#include "WorldContactListener.h"

void WorldContactListener::BeginContact(b2Contact *contact)
{
	void* ptrA = contact->GetFixtureA()->GetBody()->GetUserData();
	if (ptrA != nullptr)
	{
		static_cast<b2ContactListener*>(ptrA)->BeginContact(contact);
	}

	void* ptrB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (ptrB != nullptr)
	{
		static_cast<b2ContactListener*>(ptrB)->BeginContact(contact);
	}
}
 
void WorldContactListener::EndContact(b2Contact *contact)
{
	void* ptrA = contact->GetFixtureA()->GetBody()->GetUserData();
	if (ptrA != nullptr)
	{
		static_cast<b2ContactListener*>(ptrA)->EndContact(contact);
	}

	void* ptrB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (ptrB != nullptr)
	{
		static_cast<b2ContactListener*>(ptrB)->EndContact(contact);
	}
}

void WorldContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
	 void* ptrA = contact->GetFixtureA()->GetBody()->GetUserData();
	if (ptrA != nullptr)
	{
		static_cast<b2ContactListener*>(ptrA)->PreSolve(contact, oldManifold);
	}

	void* ptrB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (ptrB != nullptr)
	{
		static_cast<b2ContactListener*>(ptrB)->PreSolve(contact, oldManifold);
	}
}

void WorldContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
	void* ptrA = contact->GetFixtureA()->GetBody()->GetUserData();
	if (ptrA != nullptr)
	{
		static_cast<b2ContactListener*>(ptrA)->PostSolve(contact, impulse);
	}

	void* ptrB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (ptrB != nullptr)
	{
		static_cast<b2ContactListener*>(ptrB)->PostSolve(contact, impulse);
	}
}