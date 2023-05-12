#pragma once

#include "IComponent.h"
#include "ISensor.h"

#include "PhysicComponent.h"
#include "WorldContactListener.h"
#include "Bitmask.h"

#include "FixtureManager.h"

#include "ILevelSwitcher.h"

#include "OnLevelSwitchEvent.h"
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

			physicComponent->AddSensor(boxFixtureDef);
		}

		collisionMask.SetBit((uint16)CollisionLayers::Player);
		collisionMask.SetBit((uint16)CollisionLayers::LevelSwitcher);

		WorldContactListener::AddHandler(collisionMask, this);
	}

	void OnCollisionEnter(b2Contact* contact) override 
	{
		Debug::Log("---------------" + std::to_string((short)levelToTransit));

		//objectContext.sceneManager->SwitchToScene(0);
		levelSwitcher->EnableDraw();
	}
	void OnCollisionExit(b2Contact* contact) override 
	{
		Debug::Log("---------------");
		levelSwitcher->DisableDraw();
	}

	void OnDestroy() override
	{
		WorldContactListener::DeleteComponentHandler(componentId);
	}

	void SwitchToLevel(GameLevels level)
	{
		EventData eventData(OnLevelSwitchEvent::GetType());

		auto userData = new OnLevelSwitchData;
		userData->level = level;
		eventData.userData = userData;

		OnLevelSwitchEvent::Invoke(eventData);

		delete userData;
	}

private:
	PhysicComponent* physicComponent;
	Bitmask collisionMask;

	GameLevels levelToTransit;

	ILevelSwitcher* levelSwitcher;

	sf::Vector2f size = { 20.f, 50.f };

};

