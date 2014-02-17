#include "WorldContactListener.h"
#include "Entity.h"

void WorldContactListener::BeginContact(b2Contact *contact)
{
	void* ptrA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* ptrB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (ptrA != nullptr && ptrB != nullptr)
	{
		Entity* entityA = static_cast<Entity*>(ptrA);
		Entity* entityB = static_cast<Entity*>(ptrB);

		entityA->BeginContact(contact, entityB);
		entityB->BeginContact(contact, entityA);
	}
}
 
void WorldContactListener::EndContact(b2Contact *contact)
{
	void* ptrA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* ptrB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (ptrA != nullptr && ptrB != nullptr)
	{
		Entity* entityA = static_cast<Entity*>(ptrA);
		Entity* entityB = static_cast<Entity*>(ptrB);

		entityA->EndContact(contact, entityB);
		entityB->EndContact(contact, entityA);
	}
}

void WorldContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
	void* ptrA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* ptrB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (ptrA != nullptr && ptrB != nullptr)
	{
		Entity* entityA = static_cast<Entity*>(ptrA);
		Entity* entityB = static_cast<Entity*>(ptrB);

		entityA->PreSolve(contact, oldManifold, entityB);
		entityB->PreSolve(contact, oldManifold, entityA);
	}
}

void WorldContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
	void* ptrA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* ptrB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (ptrA != nullptr && ptrB != nullptr)
	{
		Entity* entityA = static_cast<Entity*>(ptrA);
		Entity* entityB = static_cast<Entity*>(ptrB);

		entityA->PostSolve(contact, impulse, entityB);
		entityB->PostSolve(contact, impulse, entityA);
	}
}