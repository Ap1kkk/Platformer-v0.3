#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
	Debug::LogInfo("Created with id: " + std::to_string(componentId), typeid(*this).name());
}

void TransformComponent::AddPosition(sf::Vector2f position)
{
	this->position += position;
}

void TransformComponent::AddPosition(float x, float y)
{
	this->position.x += x;
	this->position.y += y;
}

void TransformComponent::SetPosition(sf::Vector2f position)
{
	this->position = position;
}

void TransformComponent::SetPosition(float x, float y)
{
	this->position.x = x;
	this->position.y = y;
}

sf::Vector2f& TransformComponent::GetPosition()
{
	return position;
}
