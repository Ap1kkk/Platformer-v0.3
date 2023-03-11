#pragma once

#include "Component.h"
#include "Debug.h"

class TransformComponent : public Component
{
public:
	TransformComponent() : Component() {}
	~TransformComponent() 
	{
		Debug::LogWarning("Destructor", typeid(*this).name());
	}

	void SetPosition(sf::Vector2f position)
	{
		this->position = position;
	}
	void SetPosition(float x, float y)
	{
		this->position.x = x;
		this->position.y = y;
	}

	sf::Vector2f& GetPosition()
	{
		return position;
	}

private:
	sf::Vector2f position;
};