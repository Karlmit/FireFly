#include "RayCastCallback.h"
#include "Entity.h"

RayCastCallback::RayCastCallback()
	: hit(false)
{
}

float32 RayCastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	void* userData =  fixture->GetBody()->GetUserData();
	if (userData != nullptr)
	{
		Entity* entity =  static_cast<Entity*>(userData);
		if (entity->getID() == "StaticCollider" || entity->getID() == "CoatHoleCollision")
		{	
			this->fixture = fixture;
			this->point = point;
			this->normal = normal;
			this->fraction = fraction;
			this->hit = true;

			return fraction;
		}
	}

	return 1;
}