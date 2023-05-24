#pragma once

#include "IComponent.h"
#include "ISensor.h"

#include "ILevelFinisher.h"

#include "PhysicComponent.h"

#include "FixtureManager.h"

#include "WorldContactListener.h"

class LevelFinisherSensor : public IComponent
{
public:
	void SetPhysicComponent(PhysicComponent* physicComponent)
	{
		this->physicComponent = physicComponent;
	}

	void SetILevelFinisher(ILevelFinisher* levelFinisher)
	{
		this->levelFinisher = levelFinisher;
	}

	void Awake() override
	{
		{
			b2PolygonShape boxShape;
			boxShape.SetAsBox(size.x, size.y);

			b2FixtureDef boxFixtureDef;
			boxFixtureDef.shape = &boxShape;
			boxFixtureDef.isSensor = true;
			boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::LevelFinisher));
			boxFixtureDef.filter.maskBits = (1 << ((uint16)CollisionLayers::Player));

			sensor = physicComponent->AddSensor(boxFixtureDef);
		}

		collisionMask.SetBit((uint16)CollisionLayers::Player);
		collisionMask.SetBit((uint16)CollisionLayers::LevelFinisher);

		WorldContactListener::AddHandler(collisionMask, this);
	}

	void OnCollisionEnter(b2Contact* contact) override
	{
		auto fix1 = FixtureManager::GetFixture(contact->GetFixtureA()->GetUserData().pointer);
		auto fix2 = FixtureManager::GetFixture(contact->GetFixtureB()->GetUserData().pointer);

		if (fix1 != nullptr && fix2 != nullptr)
		{
			if (fix1->GetFixtureId() == sensor->GetFixtureId() || fix2->GetFixtureId() == sensor->GetFixtureId())
			{
				Debug::Log("--------------- finisher");
				levelFinisher->EnableDraw();
			}
		}

	}
	void OnCollisionExit(b2Contact* contact) override
	{
		auto fix1 = FixtureManager::GetFixture(contact->GetFixtureA()->GetUserData().pointer);
		auto fix2 = FixtureManager::GetFixture(contact->GetFixtureB()->GetUserData().pointer);

		if (fix1 != nullptr && fix2 != nullptr)
		{
			if (fix1->GetFixtureId() == sensor->GetFixtureId() || fix2->GetFixtureId() == sensor->GetFixtureId())
			{
				Debug::Log("--------------- finisher");
				levelFinisher->DisableDraw();
			}
		}
	}

	void OnDestroy() override
	{
		WorldContactListener::DeleteComponentHandler(componentId); 
	}

private:
	PhysicComponent* physicComponent;
	Bitmask collisionMask;
	Sensor* sensor;

	ILevelFinisher* levelFinisher;

	sf::Vector2f size = { 100.f, 150.f };
};

