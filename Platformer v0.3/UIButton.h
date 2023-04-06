#pragma once

#include "SFML/Graphics.hpp"
#include "UIObject.h"
#include "Debug.h"

class UIButton : public UIObject
{
public:
	UIButton() {}

	void Awake() override
	{
		Initialize(true, drawLayer);
		SetTexture("floor.png");
		SetUIPosition(position);
		spriteBounds = drawableComponent->GetSpriteBounds();
	}

	void CaptureMousePosition()
	{
		//auto mousePosition = sf::Mouse::getPosition();
		if (spriteBounds.contains(mousePosition.x, mousePosition.y))
		{
			Debug::Log("Intersection");
		}
	}

	void UpdateUI() override
	{
		CaptureMousePosition();
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
	
	void SetDrawLayer(DrawLayer drawlayer)
	{
		this->drawLayer = drawLayer;
	}

private:
	DrawLayer drawLayer = 200;
	sf::Vector2f position;

	sf::FloatRect spriteBounds;
};

