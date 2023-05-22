#pragma once

#include <string>

#include "IComponent.h"
#include "ISensor.h"

#include "PhysicComponent.h"

#include "GameObject.h"
#include "WorldContactListener.h"


class JumpSensor : public IComponent, public ISensor
{
public:
	JumpSensor() {}
	~JumpSensor()
	{
		Debug::LogWarning("Destroyed");
	}

	void SetPhysicComponent(PhysicComponent* physicComponent);

	void SetOffset(sf::Vector2f offset);

	void Awake() override;

	bool IsEnabledToJump() const { return intersectsCount; }
	
	void OnCollisionEnter(b2Contact* contact) override;

	void OnCollisionExit(b2Contact* contact) override;

	void OnDestroy() override;

private:
	void EnterCollision() { ++intersectsCount; }
	void LeaveCollision() 
	{ 
		--intersectsCount;
		if (intersectsCount == 0)
		{
			EventData data(EventType::OnJumpSensorLeftCollisions);
			Event::Invoke(data);
		}
	}

	unsigned int intersectsCount = 0;

	b2Body* body;
	b2Vec2 ownerBodyOffset;
	Sensor* sensor;
	PhysicComponent* physicComponent;

	bool isEnabledToJump;

	Bitmask collisionMask;
};

