#pragma once

#include "UIObject.h"
#include "DataTypes.h"

#include "SaveManager.h"

class MenuBackground : public UIObject
{
public:
	MenuBackground() {}

	void Awake() override
	{
		Initialize();
		AddSpriteComponent(drawLayer);
		if (SaveManager::IsGameOver())
		{
			SetTexture(textureFilenameGameOver);
		}
		else if (SaveManager::IsGameWon())
		{
			SetTexture(textureFilenameGameWon);
		}
		else
		{
			SetTexture(textureFilename);
		}
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
	Filename textureFilenameGameOver = "Menu/game_over.png";
	Filename textureFilenameGameWon = "Menu/game_won.png";
};