#pragma once

#include "IComponent.h"
#include "ISensor.h"

#include "PhysicComponent.h"
#include "WorldContactListener.h"
#include "Bitmask.h"

#include "FixtureManager.h"

#include "ILevelSwitcher.h"

#include "OnLevelSwitchData.h"

class LevelSwitcherSensor : public IComponent, public ISensor
{
public:
	LevelSwitcherSensor() {}

	void SetPhysicComponent(PhysicComponent* physicComponent)
	{
		this->physicComponent = physicComponent;
	}
	
	void SetILevelSwitcher(ILevelSwitcher* levelSwitcher)
	{
		this->levelSwitcher = levelSwitcher;
	}

	void SetLevelToTransit(GameLevels level)
	{
		levelToTransit = level;
	}

	void Awake() override
	{
		{
			b2PolygonShape boxShape;
			boxShape.SetAsBox(size.x, size.y);

			b2FixtureDef boxFixtureDef;
			boxFixtureDef.shape = &boxShape;
			boxFixtureDef.isSensor = true;
			boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::LevelSwitcher));
			boxFixtureDef.filter.maskBits = (1 << ((uint16)CollisionLayers::Player));

			sensor = physicComponent->AddSensor(boxFixtureDef);
		}

		collisionMask.SetBit((uint16)CollisionLayers::Player);
		collisionMask.SetBit((uint16)CollisionLayers::LevelSwitcher);

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
				Debug::Log("---------------" + std::to_string((short)levelToTransit));
				levelSwitcher->EnableDraw();
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
				Debug::Log("---------------");
				levelSwitcher->DisableDraw();
			}
		}
	}

	void OnDestroy() override
	{
		WorldContactListener::DeleteComponentHandler(componentId);
	}

	void SwitchToLevel(GameLevels level)
	{
		EventData eventData(EventType::OnLevelSwitchEvent);

		auto userData = new OnLevelSwitchData;
		userData->level = level;
		eventData.userData = userData;

		Event::Invoke(eventData);

		delete userData;
	}

private:
	PhysicComponent* physicComponent;
	Bitmask collisionMask;

	Sensor* sensor;

	GameLevels levelToTransit;

	ILevelSwitcher* levelSwitcher;

	sf::Vector2f size = { 100.f, 150.f };

};

