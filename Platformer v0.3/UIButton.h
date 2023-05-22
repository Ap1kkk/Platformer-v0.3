#pragma once

#include "SFML/Graphics.hpp"
#include "UIObject.h"
#include "Debug.h"

#include "Input.h"

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

	virtual void OnButtonHover()
	{
		
	}
	virtual void OnButtonClick()
	{
		//Debug::Log("Click");

		//if (drawableSpriteComponent->IsEnabled())
		//{
		//	drawableSpriteComponent->Disable();
		//}
		//else
		//{
		//	drawableSpriteComponent->Enable();
		//}
	}

private:
	DrawLayer drawLayer = 200;
	sf::Vector2f position;

	sf::FloatRect spriteBounds;
};

