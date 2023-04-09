#pragma once

#include "IComponent.h"
#include "ISensor.h"

#include "PhysicComponent.h"
#include "WorldContactListener.h"
#include "Bitmask.h"

#include "Debug.h"

class AttackSensor : public IComponent, public ISensor
{
public:
	AttackSensor() {}

	void SetPhysicComponent(PhysicComponent* physicComponent);

	void SetOffset(sf::Vector2f offset);

	void Awake() override;

	void OnCollisionEnter(b2Contact* contact) override;
	void OnCollisionExit(b2Contact* contact) override;

	void OnDestroy() override;

private:
	b2Body* body;
	b2Vec2 ownerBodyOffset;
	Sensor* sensor;
	PhysicComponent* physicComponent;
	Bitmask collisionMask;

	bool isEnabledToJump;
};

