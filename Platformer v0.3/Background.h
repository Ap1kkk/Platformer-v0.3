#pragma once

#include "GameObject.h"
#include "DataTypes.h"

class Background : public GameObject
{
public:
	Background()
	{
		Debug::LogInfo("Created with id: " + std::to_string(entityId), typeid(*this).name());
	}

	void Awake() override
	{
		MakeDrawable(true, drawLayer);
		SetTexture(textureFilename);
	}

	void SetPosition(sf::Vector2f position)
	{
		//auto spriteBounds = drawableComponent->GetSpriteBounds();
		transform->SetPosition(sf::Vector2f(position.x, position.y));
	}

private:
	DrawLayer drawLayer = -100;
	Filename textureFilename = "forest.png";
};

