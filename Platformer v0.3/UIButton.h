#pragma once

#include "SFML/Graphics.hpp"
#include "UIObject.h"
#include "Debug.h"

#include "Input.h"

class UIButton : public UIObject
{
public:
	UIButton() {}

	void CaptureMousePosition();

	void UpdateUI() override;

	void SetPosition(sf::Vector2f position);
	void SetPosition(float x, float y);
	
	void SetDrawLayer(DrawLayer drawlayer);

	virtual void OnButtonHover() {}
	virtual void OnButtonClick() = 0;

protected:
	sf::Vector2f position;
	sf::FloatRect spriteBounds;

private:
	DrawLayer drawLayer = 200;

};

