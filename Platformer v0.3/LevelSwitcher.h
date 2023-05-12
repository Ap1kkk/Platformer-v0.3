#pragma once

#include "ILevelSwitcher.h"

#include "GameObject.h"
#include "LevelSwitcherSensor.h"


class LevelSwitcher : public GameObject, public ILevelSwitcher
{
public:

	void Awake() override
	{
		MakePhysical();

		AddSpriteComponent(false, drawLayer);
		SetTexture(textureFilename);

		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position = b2Vec2(spawnPosition.x, spawnPosition.y);
		physicComponent->SetBodyDef(bodyDef);
		physicComponent->InitializeBody();

		levelSwitcherSensor = AddComponent<LevelSwitcherSensor>();
		levelSwitcherSensor->SetPhysicComponent(physicComponent);
		levelSwitcherSensor->SetILevelSwitcher(this);
		levelSwitcherSensor->SetLevelToTransit(levelToSwitch);
	}

	void SetPosition(const sf::Vector2f& position)
	{
		transform->SetPosition(sf::Vector2f(position.x, position.y));
		SetSpawnPosition(position);
	}

	void SetSensorSize(const sf::Vector2f& size)
	{
		this->size = size;
	}

	void SetLevelTotransit(GameLevels level)
	{
		levelToSwitch = level;
	}

	void EnableDraw() override
	{
		EnableToDraw();
		//TODO добавить включение компонента обработчика перехода
	}

	void DisableDraw() override
	{
		DisableToDraw();
	}

	void OnDestroy() override
	{
		
	}

private:
	sf::Vector2f size = { 20.f, 50.f };
	LevelSwitcherSensor* levelSwitcherSensor;
	GameLevels levelToSwitch;

	DrawLayer drawLayer = 100;
	Filename textureFilename = "floor.png";
};

