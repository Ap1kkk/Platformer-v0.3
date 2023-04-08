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

	//class JumpSensorListener : public b2ContactListener
	//{
	//	void BeginContact(b2Contact* contact) override
	//	{
	//		if (contact )
	//		{
	//			auto fixtureA = static_cast<Fixture*>(contact->GetFixtureA());
	//			auto fixtureB = static_cast<Fixture*>(contact->GetFixtureB());

	//			switch (fixtureA->GetFilterData().categoryBits | fixtureB->GetFilterData().categoryBits) 
	//			{
	//			case (uint16)CollisionLayers::Ground | (uint16)CollisionLayers::Sensor:
	//			{
	//				auto entity1 = EntityManager::GetEntityById<GameObject>(PhysicSystem::GetBodyOwnerId(fixtureA->GetBody()));
	//				auto entity2 = EntityManager::GetEntityById<GameObject>(PhysicSystem::GetBodyOwnerId(fixtureB->GetBody()));

	//				if (entity1 != nullptr && entity2 != nullptr)
	//				{
	//					JumpSensor* sensor = entity1->GetComponent<JumpSensor>();
	//					JumpSensor* other = entity2->GetComponent<JumpSensor>();

	//					if (sensor != nullptr)
	//					{
	//						sensor->EnterCollision();
	//						Debug::Log("enabled " + std::to_string(sensor->IsEnabledToJump()));

	//					}
	//					else if (other != nullptr)
	//					{
	//						other->EnterCollision();
	//						Debug::Log("enabled " + std::to_string(other->IsEnabledToJump()));

	//					}
	//				} 
	//			}
	//				break;

	//			case (uint16)CollisionLayers::Player | (uint16)CollisionLayers::Sensor:
	//				Debug::Log("Contacted");
	//				break;
	//			}
	//		}
	//	}

	//	void EndContact(b2Contact* contact) override
	//	{
	//		if (contact)
	//		{
	//			auto fixtureA = static_cast<Fixture*>(contact->GetFixtureA());
	//			auto fixtureB = static_cast<Fixture*>(contact->GetFixtureB());

	//			switch (fixtureA->GetFilterData().categoryBits | fixtureB->GetFilterData().categoryBits)
	//			{
	//			case (uint16)CollisionLayers::Ground | (uint16)CollisionLayers::Sensor:
	//				auto entity1 = EntityManager::GetEntityById<GameObject>(PhysicSystem::GetBodyOwnerId(fixtureA->GetBody()));
	//				auto entity2 = EntityManager::GetEntityById<GameObject>(PhysicSystem::GetBodyOwnerId(fixtureB->GetBody()));

	//				if (entity1 != nullptr && entity2 != nullptr)
	//				{
	//					JumpSensor* sensor = entity1->GetComponent<JumpSensor>();
	//					JumpSensor* other = entity2->GetComponent<JumpSensor>();

	//					if (sensor != nullptr)
	//					{
	//						sensor->LeaveCollision();
	//						Debug::Log("enabled " + std::to_string(sensor->IsEnabledToJump()));

	//					}
	//					else if (other != nullptr)
	//					{
	//						other->LeaveCollision();
	//						Debug::Log("enabled " + std::to_string(other->IsEnabledToJump()));

	//					}
	//				}
	//			}
	//		}
	//	}
	//};

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
		boxFixtureDef.filter.categoryBits = (uint16)CollisionLayers::JumpSensor;
		boxFixtureDef.filter.maskBits = (uint16)CollisionLayers::Ground | (uint16)CollisionLayers::Default | (uint16)CollisionLayers::Enemy;
		
		//TODO добавить маску слоев коллизий
		
		sensor = physicComponent->AddSensor(boxFixtureDef);

		worldContactListener = new WorldContactListener;

		collisionMask.SetBit((uint16)CollisionLayers::Ground);
		collisionMask.SetBit((uint16)CollisionLayers::JumpSensor);
		worldContactListener->AddHandler(collisionMask, this);

		PhysicSystem::SetContactListener<WorldContactListener>(worldContactListener);
	}

	bool IsEnabledToJump() const { return intersectsCount; }
	
	void OnCollisionEnter(b2Contact* contact) override
	{
		Debug::Log("Enter");
	}

	void OnCollisionExit(b2Contact* contact) override
	{
		Debug::Log("Exit");
	}

	void OnDestroy() override
	{
		delete worldContactListener;
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

	//TODO убрать костыль
	WorldContactListener* worldContactListener;
};

