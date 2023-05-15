#pragma once

#include "Entity.h"
#include "TransformUIComponent.h"
#include "Window.h"

#include "DrawableSpriteComponent.h"
#include "DrawableTextComponent.h"

class UIObject : public Entity
{
public:
	UIObject();

	void Initialize(DrawLayer drawLayer);

	void SetTexture(const std::string& filename);

	void SetTextureRect(const std::string& filename, sf::IntRect intRect);

	void SetUIPosition(sf::Vector2f position);

protected:
	DrawableSpriteComponent* drawableSpriteComponent;
	DrawableTextComponent* drawableTextComponent;
	TransformUIComponent* transformUI;

	bool isEnabledToDraw = true;
	DrawLayer drawLayer;

	sf::Vector2f position;
};

