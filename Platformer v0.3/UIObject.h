#pragma once

#include "Entity.h"
#include "DrawableComponent.h"
#include "Window.h"

class UIObject : public Entity
{
public:
	UIObject()
	{
		drawableComponent = AddComponent<DrawableComponent>();
	}

	void SetTexture(const std::string& filename)
	{
		drawableComponent->SetTexture(filename);
	}

	void SetTextureRect(const std::string& filename, sf::IntRect intRect)
	{
		drawableComponent->SetTextureRect(filename, intRect);
	}
	
	void UpdateViewCenter() override
	{
		viewCenter = objectContext.window->GetCentre();

		CorrectUIPosition(viewCenter);
	}
	//TODO считать позицию относительно центра VIew



protected:
	DrawableComponent* drawableComponent;
	sf::Vector2u viewCenter;
};

