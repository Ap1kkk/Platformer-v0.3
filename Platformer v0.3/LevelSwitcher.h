#pragma once

#include "ILevelSwitcher.h"

#include "GameObject.h"

#include "LevelSwitcherSensor.h"
#include "LevelSwitcherComponent.h"

class LevelSwitcher : public GameObject, public ILevelSwitcher
{
public:
	LevelSwitcher() : isReadyToSwitch(false) {}

	void Awake() override
	{
		MakePhysical();

		//AddSpriteComponent(drawLayer);
		//drawableSpriteComponent->Disable();
		//SetTexture(textureFilename);

		AddTextComponent(drawLayer);
		drawableTextComponent->Disable();
		drawableTextComponent->SetFont(AssetAllocator::GetFont(AssetAllocator::GetPath() + fontFilename));
		drawableTextComponent->SetText("    Press E    \nTo switch level");


		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position = b2Vec2(spawnPosition.x, spawnPosition.y);
		physicComponent->SetBodyDef(bodyDef);
		physicComponent->InitializeBody();

		levelSwitcherSensor = AddComponent<LevelSwitcherSensor>();
		levelSwitcherSensor->SetPhysicComponent(physicComponent);
		levelSwitcherSensor->SetILevelSwitcher(this);
		levelSwitcherSensor->SetLevelToTransit(levelToSwitch);

		levelSwitcherComponent = AddComponent<LevelSwitcherComponent>();
		levelSwitcherComponent->Disable();
		
		//TODO ÏÎÌÅÍßÒÜ ÍÀ ENUM
		levelSwitcherComponent->SetLevelToSwitch(levelToSwitch);
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
		//drawableSpriteComponent->Enable();
		drawableTextComponent->Enable();

		levelSwitcherComponent->Enable();

	}

	void DisableDraw() override
	{
		//drawableSpriteComponent->Disable();
		drawableTextComponent->Disable();

		levelSwitcherComponent->Disable();

	}

	void OnDestroy() override
	{
		
	}

private:
	sf::Vector2f size = { 20.f, 50.f };
	LevelSwitcherSensor* levelSwitcherSensor;
	LevelSwitcherComponent* levelSwitcherComponent;
	GameLevels levelToSwitch;

	DrawLayer drawLayer = 100;
	Filename textureFilename = "floor.png";
	Filename fontFilename = "Fonts/BenguiatStd-Bold.otf";

	bool isReadyToSwitch;
};

