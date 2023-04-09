#pragma once

#include "SFML/Graphics.hpp"
#include "UIObject.h"
#include "Debug.h"

class UIButton : public UIObject
{
public:
	UIButton() {}

	void Awake() override;

	void CaptureMousePosition();

	void UpdateUI() override;

	void SetPosition(sf::Vector2f position);
	void SetPosition(float x, float y);
	
	void SetDrawLayer(DrawLayer drawlayer);

private:
	DrawLayer drawLayer = 200;
	sf::Vector2f position;

	sf::FloatRect spriteBounds;
};

