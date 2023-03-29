#pragma once

#include "IComponent.h"

#include "PhysicComponent.h"
#include "ISensor.h"



class JumpSensor : public IComponent, public ISensor
{
public:
	JumpSensor() {}

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

				JumpSensor* other = reinterpret_cast<JumpSensor*>(firstPtr);

				//Debug::LogInfo("1");
			}
		}

		void EndContact(b2Contact* contact) override
		{

		}
	};

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
		//TODO добавить маску слоев коллизий
		boxFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
		
		sensor = physicComponent->AddSensor(boxFixtureDef);
		auto listener = new JumpSensorListener;

		PhysicSystem::SetContactListener<JumpSensorListener>(listener);
		//auto userData = reinterpret_cast<JumpSensor*>(fixture->GetUserData().pointer);
		
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
	Sensor* sensor;
	PhysicComponent* physicComponent;
};

