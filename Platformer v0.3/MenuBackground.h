#pragma once

#include "UIObject.h"
#include "DataTypes.h"

class MenuBackground : public UIObject
{
public:
	MenuBackground() {}

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
	sf::Vector2f position;
	DrawLayer drawLayer = -200;
	Filename textureFilename = "Menu/menu_background.png";

};