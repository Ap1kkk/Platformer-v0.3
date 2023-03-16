#pragma once

#include "Component.h"
#include "Debug.h"

class TransformComponent : public Component
{
public:
	TransformComponent() 
	{
		Debug::LogInfo("Created with id: " + std::to_string(componentId), typeid(*this).name());
	}
	~TransformComponent() 
	{
		//Debug::LogWarning("Destructor", typeid(*this).name());
	}

	void AddPosition(sf::Vector2f position)
	{
		this->position += position;
	}

	void AddPosition(float x, float y)
	{
		this->position.x += x;
		this->position.y += y;
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

	//TODO добавить rotation


private:
	sf::Vector2f position;
};