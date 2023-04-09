#pragma once

#include "Entity.h"
#include "DrawableComponent.h"
#include "TransformUIComponent.h"
#include "Window.h"

class UIObject : public Entity
{
public:
	UIObject();

	void Initialize(bool isEnabledToDraw, DrawLayer drawLayer);

	void SetTexture(const std::string& filename);

	void SetTextureRect(const std::string& filename, sf::IntRect intRect);

	void SetUIPosition(sf::Vector2f position);

protected:
	DrawableComponent* drawableComponent;
	TransformUIComponent* transformUI;

	bool isEnabledToDraw = true;
	DrawLayer drawLayer;

	sf::Vector2f position;
};

