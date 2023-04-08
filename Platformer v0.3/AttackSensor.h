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

	void SetPhysicComponent(PhysicComponent* physicComponent)
	{
		this->physicComponent = physicComponent;
	}

	void SetOffset(sf::Vector2f offset)
	{
		ownerBodyOffset = { offset.x, offset.y };
	}

	void Awake() override
	{
		b2PolygonShape boxShape;
		b2Vec2 size = { 20, 50 };
		boxShape.SetAsBox(size.x, size.y, ownerBodyOffset, 0);

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.isSensor = true;
		boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::AttackSensor));
		boxFixtureDef.filter.maskBits = (1 << ((uint16)CollisionLayers::Enemy));

		sensor = physicComponent->AddSensor(boxFixtureDef);

		collisionMask.SetBit((uint16)CollisionLayers::Enemy);
		collisionMask.SetBit((uint16)CollisionLayers::AttackSensor);

		Debug::Log("attack mask");
		Debug::Log(collisionMask.GetMask());
		WorldContactListener::AddHandler(collisionMask, this);
	}

	void OnCollisionEnter(b2Contact* contact) override
	{
		if (contact)
		{
			Debug::Log("Entered attack sensor");
		}
	}
	void OnCollisionExit(b2Contact* contact) override
	{
		if (contact)
		{
			Debug::Log("Leaved attack sensor");
		}
	}

	void OnDestroy() override
	{
		WorldContactListener::DeleteComponentHandler(componentId);
	}

private:
	b2Body* body;
	b2Vec2 ownerBodyOffset;
	Sensor* sensor;
	PhysicComponent* physicComponent;
	Bitmask collisionMask;

	bool isEnabledToJump;
};

