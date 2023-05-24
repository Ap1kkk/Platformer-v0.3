#pragma once

#include "UIObject.h"
#include "DataTypes.h"

class MenuLogo : public UIObject
{
public:
	MenuLogo(){}

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
	DrawLayer drawLayer = 400;
	Filename textureFilename = "Menu/main_menu_logo.png";

};