#pragma once

#include "IComponent.h"
#include "Debug.h"

/// <summary>
/// Contains position and rotation of an object
/// Transforms synchronized with physic world
/// </summary>
class TransformComponent : public IComponent
{
public:
	TransformComponent();
	~TransformComponent() {}

	void AddPosition(sf::Vector2f position);
	void AddPosition(float x, float y);

	void SetPosition(sf::Vector2f position);
	void SetPosition(float x, float y);

	sf::Vector2f& GetPosition();

	//TODO добавить rotation


private:
	sf::Vector2f position;
};