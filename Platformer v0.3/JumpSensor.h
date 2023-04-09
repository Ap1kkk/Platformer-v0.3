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

	void SetPhysicComponent(PhysicComponent* physicComponent)
	{
		this->physicComponent = physicComponent;
	}

	void SetOffset(sf::Vector2f offset)
	{
		ownerBodyOffset = { offset.x, offset.y};
	}

	void Awake() override
	{
		b2PolygonShape boxShape;
		b2Vec2 size = {10, 6};
		boxShape.SetAsBox(size.x, size.y, ownerBodyOffset, 0);
		
		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.isSensor = true;
		boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::JumpSensor));
		boxFixtureDef.filter.maskBits = (1 << ((uint16)CollisionLayers::Ground)) | (1 << ((uint16)CollisionLayers::Default)) | (1 << ((uint16)CollisionLayers::Enemy)) | (1 << ((uint16)CollisionLayers::SmallObstacle));
		
		Debug::Log(boxFixtureDef.filter.categoryBits);
		Debug::Log(boxFixtureDef.filter.maskBits);

		//TODO добавить маску слоев коллизий
		
		sensor = physicComponent->AddSensor(boxFixtureDef);

		collisionMask.SetBit((uint16)CollisionLayers::Ground);
		collisionMask.SetBit((uint16)CollisionLayers::JumpSensor);
		collisionMask.SetBit((uint16)CollisionLayers::SmallObstacle);
		WorldContactListener::AddHandler(collisionMask, this);
	}

	bool IsEnabledToJump() const { return intersectsCount; }
	
	void OnCollisionEnter(b2Contact* contact) override
	{
		if (contact)
		{
			Debug::Log("Entered Collision");
			EnterCollision();
		}
	}

	void OnCollisionExit(b2Contact* contact) override
	{
		if (contact)
		{
			Debug::Log("Leaved Collision");
			LeaveCollision();
		}
	}

	void OnDestroy() override
	{
		WorldContactListener::DeleteComponentHandler(componentId);
	}

private:
	void EnterCollision() { ++intersectsCount; }
	void LeaveCollision() { --intersectsCount; }

	unsigned int intersectsCount = 0;

	b2Body* body;
	b2Vec2 ownerBodyOffset;
	Sensor* sensor;
	PhysicComponent* physicComponent;

	bool isEnabledToJump;

	Bitmask collisionMask;
};

