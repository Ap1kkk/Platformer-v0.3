#pragma once

#include "GameObject.h"
#include "ILevelFinisher.h"

#include "LevelFinisherComponent.h"
#include "LevelFinisherSensor.h"

class LevelFinisher : public GameObject, public ILevelFinisher
{
public:

	void Awake() override
	{
		MakePhysical();

		AddSpriteComponent(drawLayer);
		SetTexture(textureFilename);

		AddTextComponent(drawLayer);
		drawableTextComponent->Disable();
		drawableTextComponent->SetFont(AssetAllocator::GetFont(AssetAllocator::GetPath() + fontFilename));
		drawableTextComponent->SetText("    Press E    \nTo finish level");
		drawableTextComponent->SetPositionOffset(textOffset);


		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position = b2Vec2(spawnPosition.x, spawnPosition.y);
		physicComponent->SetBodyDef(bodyDef);
		physicComponent->InitializeBody();

		levelSwitcherSensor = AddComponent<LevelFinisherSensor>();
		levelSwitcherSensor->SetPhysicComponent(physicComponent);
		levelSwitcherSensor->SetILevelFinisher(this);

		levelSwitcherComponent = AddComponent<LevelFinisherComponent>();
		levelSwitcherComponent->Disable();

	}

	void SetPosition(const sf::Vector2f& position)
	{
		transform->SetPosition(sf::Vector2f(position.x, position.y));
		SetSpawnPosition(position);
	}


	void EnableDraw() override
	{
		drawableTextComponent->Enable();

		levelSwitcherComponent->Enable();

	}

	void DisableDraw() override
	{
		drawableTextComponent->Disable();

		levelSwitcherComponent->Disable();

	}

private:
	//sf::Vector2f size = { 20.f, 50.f };
	LevelFinisherSensor* levelSwitcherSensor;
	LevelFinisherComponent* levelSwitcherComponent;
	
	DrawLayer drawLayer = 100;
	Filename fontFilename = "Fonts/BenguiatStd-Bold.otf";

	Filename textureFilename = "Characters/finish_character.png";

	sf::Vector2f textOffset = { 0.f, -100.f };

	bool isReadyToSwitch;
};

