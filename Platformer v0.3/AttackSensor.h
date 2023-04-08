#pragma once

#include "IComponent.h"
#include "ISensor.h"

#include "PhysicComponent.h"

#include "GameObject.h"

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
		boxFixtureDef.filter.categoryBits = (uint16)CollisionLayers::Sensor;
		boxFixtureDef.filter.maskBits = (uint16)CollisionLayers::Player;

		sensor = physicComponent->AddSensor(boxFixtureDef);
		//attackListener = new AttackSensorListener;

		//PhysicSystem::SetContactListener<AttackSensorListener>(attackListener);
	}

	void OnDestroy() override
	{
		//delete attackListener;
	}

private:
	b2Body* body;
	b2Vec2 ownerBodyOffset;
	Sensor* sensor;
	//AttackSensorListener* attackListener;
	PhysicComponent* physicComponent;

	bool isEnabledToJump;
};

