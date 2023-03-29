#pragma once

#include <box2d/box2d.h>

#include "GameObject.h"
#include "JumpSensor.h"

class JumpSensorListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) override
	{
		if (contact && contact->IsTouching())
		{
			auto firstPtr = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
			//JumpSensor* A = reinterpret_cast<JumpSensor*>(firstPtr);

			auto secondPtr = contact->GetFixtureB()->GetBody()->GetUserData().pointer;
			//JumpSensor* B = reinterpret_cast<JumpSensor*>(secondPtr);

			GameObject* other = reinterpret_cast<GameObject*>(firstPtr);
		}
	}

	void EndContact(b2Contact* contact) override
	{

	}
};

