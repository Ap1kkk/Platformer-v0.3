#pragma once

#include "IComponent.h"

#include "PhysicComponent.h"
#include "ISensor.h"

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
		boxFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
		
		auto fixture = physicComponent->AddFixtureDef(boxFixtureDef);

		//auto userData = reinterpret_cast<JumpSensor*>(fixture->GetUserData());
		
	}

	void Something()
	{
		Debug::Log("Something");
	}

	void Update() override
	{

	}

private:
	b2Body* body;
	b2Vec2 ownerBodyOffset;
	PhysicComponent* physicComponent;
};

