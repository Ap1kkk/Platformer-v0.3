#pragma once

#include <string>

#include "IComponent.h"
#include "ISensor.h"

#include "PhysicComponent.h"

#include "GameObject.h"



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
				auto fixtureA = static_cast<Fixture*>(contact->GetFixtureA());
				auto fixtureB = static_cast<Fixture*>(contact->GetFixtureB());

				if (fixtureA->IsSensor() || fixtureB->IsSensor())
				{
					auto entity1 = EntityManager::GetEntityById<GameObject>(PhysicSystem::GetBodyOwnerId(fixtureA->GetBody()));
					auto entity2 = EntityManager::GetEntityById<GameObject>(PhysicSystem::GetBodyOwnerId(fixtureB->GetBody()));

					if (entity1 != nullptr && entity2 != nullptr)
					{
						JumpSensor* sensor = entity1->GetComponent<JumpSensor>();
						JumpSensor* other = entity2->GetComponent<JumpSensor>();

						if (sensor != nullptr)
						{
							sensor->EnterCollision();
							Debug::Log("enabled " + std::to_string(sensor->IsEnabledToJump()));
						}
						else if (other != nullptr)
						{
							other->EnterCollision();
							Debug::Log("enabled " + std::to_string(other->IsEnabledToJump()));
						}
					}
				}
			}
		}

		void EndContact(b2Contact* contact) override
		{
			if (contact)
			{
				auto fixtureA = static_cast<Fixture*>(contact->GetFixtureA());
				auto fixtureB = static_cast<Fixture*>(contact->GetFixtureB());

				if (fixtureA->IsSensor() || fixtureB->IsSensor())
				{
					auto entity1 = EntityManager::GetEntityById<GameObject>(PhysicSystem::GetBodyOwnerId(fixtureA->GetBody()));
					auto entity2 = EntityManager::GetEntityById<GameObject>(PhysicSystem::GetBodyOwnerId(fixtureB->GetBody()));

					if (entity1 != nullptr && entity2 != nullptr)
					{
						JumpSensor* sensor = entity1->GetComponent<JumpSensor>();
						JumpSensor* other = entity2->GetComponent<JumpSensor>();

						if (sensor != nullptr)
						{
							sensor->LeaveCollision();
							Debug::Log("disabled " + std::to_string(sensor->IsEnabledToJump()));

						}
						else if (other != nullptr)
						{
							other->LeaveCollision();
							Debug::Log("disabled " + std::to_string(other->IsEnabledToJump()));

						}
					}
				}
			}
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
		
		sensor = physicComponent->AddSensor(boxFixtureDef);
		auto listener = new JumpSensorListener;

		PhysicSystem::SetContactListener<JumpSensorListener>(listener);
	}

	bool IsEnabledToJump() const { return intersectsCount; }

private:
	void EnterCollision() { ++intersectsCount; }
	void LeaveCollision() { --intersectsCount; }

	unsigned int intersectsCount = 0;

	b2Body* body;
	b2Vec2 ownerBodyOffset;
	Sensor* sensor;
	PhysicComponent* physicComponent;

	bool isEnabledToJump;
};

