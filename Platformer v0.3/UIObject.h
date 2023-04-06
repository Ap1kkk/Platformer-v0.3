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
		Debug::LogInfo("Created with id: " + std::to_string(entityId), typeid(*this).name());

	}

	void Initialize(bool isEnabledToDraw, DrawLayer drawLayer)
	{
		transformUI = AddComponent<TransformUIComponent>();

		transformUI->SetPosition(position);

		this->drawLayer = drawLayer;
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

	void SetUIPosition(sf::Vector2f position)
	{
		this->position = position;
		transformUI->SetPosition(position);
	}

protected:
	DrawableComponent* drawableComponent;
	TransformUIComponent* transformUI;

	bool isEnabledToDraw = true;
	DrawLayer drawLayer;

	sf::Vector2f position;
};

