#pragma once

#include "Entity.h"
#include "DrawableComponent.h"
#include "TransformUIComponent.h"
#include "Window.h"

class UIObject : public Entity
{
public:
	UIObject()
	{
	
	}

	void Initialize(bool isEnabledToDraw)
	{
		transformUI = AddComponent<TransformUIComponent>();

		transformUI->SetPosition(position);

		this->isEnabledToDraw = isEnabledToDraw;
		drawableComponent = AddComponent<DrawableComponent>();
		drawableComponent->Initialize(transformUI);
		drawableComponent->SetDrawLayer(drawLayer);
		RenderSystem::AddDrawable(entityId, drawableComponent, isEnabledToDraw);
	}

	void Awake() override
	{

	}

	void SetTexture(const std::string& filename)
	{
		drawableComponent->SetTexture(filename); 
	}

	void SetTextureRect(const std::string& filename, sf::IntRect intRect)
	{
		drawableComponent->SetTextureRect(filename, intRect);
	}

	void SetPosition(sf::Vector2f position)
	{
		this->position = position;
	}

protected:
	DrawableComponent* drawableComponent;
	TransformUIComponent* transformUI;

	bool isEnabledToDraw = true;
	DrawLayer drawLayer = 200;

	sf::Vector2f position;
};

