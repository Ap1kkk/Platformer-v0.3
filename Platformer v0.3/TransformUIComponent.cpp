#include "TransformUIComponent.h"

TransformUIComponent::TransformUIComponent()
{
	SetComponentLayer(ComponentOrder::TransfromComponent);
	Debug::LogInfo("Created with id: " + std::to_string(componentId), typeid(*this).name());
}

void TransformUIComponent::UpdateUI()
{
	auto view = objectContext.window->GetView();
	viewCenter = view.getCenter();
	//viewCenter = window->GetCentre();
	position = { viewCenter.x + initialPosition.x, viewCenter.y + initialPosition.y };
}

void TransformUIComponent::AddPosition(sf::Vector2f position)
{
	this->initialPosition += position;
}

void TransformUIComponent::AddPosition(float x, float y)
{
	this->initialPosition.x += x;
	this->initialPosition.y += y;
}

void TransformUIComponent::SetPosition(sf::Vector2f position)
{
	this->initialPosition = position;
}

void TransformUIComponent::SetPosition(float x, float y)
{
	this->initialPosition.x = x;
	this->initialPosition.y = y;
}

void TransformUIComponent::SetAngleInDeg(float angleInDeg)
{
	angle = angleInDeg;
}

void TransformUIComponent::SetAngleInRad(float angleInRad)
{
	angle = RADTODEG * angleInRad;
}

float TransformUIComponent::GetAngle() const
{
	return angle;
}

sf::Vector2f& TransformUIComponent::GetPosition()
{
	return position;
}
