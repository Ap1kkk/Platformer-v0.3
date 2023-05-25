#pragma once

#include "GameObject.h"

#include "AssetAllocator.h"
#include "DataTypes.h"
#include "Debug.h"

class LevelLabel : public GameObject
{
public:
	
	void Awake() override
	{
		AddTextComponent(drawLayer);
		drawableTextComponent->SetFont(AssetAllocator::GetFont(AssetAllocator::GetPath() + fontFilename));
		drawableTextComponent->SetTextSize(30);
		drawableTextComponent->SetText(label);

	}

	void SetLabel(std::string label)
	{
		this->label = label;
	}

	void SetPosition(const sf::Vector2f& position)
	{
		transform->SetPosition(sf::Vector2f(position.x, position.y));
		SetSpawnPosition(position);
	}

private:
	std::string label;
	Filename fontFilename = "Fonts/BenguiatStd-Bold.otf";

	DrawLayer drawLayer = 100;
};

