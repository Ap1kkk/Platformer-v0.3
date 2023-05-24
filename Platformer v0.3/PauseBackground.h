#pragma once

#include "UIObject.h"
#include "DataTypes.h"

class PauseBackground : public UIObject
{
public:
	PauseBackground(){}

	void Awake() override
	{
		Initialize();

		AddSpriteComponent(drawLayer);
		SetTexture(textureFilename);
		SetUIPosition(position);
	}


	void SetPosition(sf::Vector2f position)
	{
		this->position = position;
	}

	void SetPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

private:
	DrawLayer drawLayer = -200;
	Filename textureFilename = "Menu/pause_background.png";

};