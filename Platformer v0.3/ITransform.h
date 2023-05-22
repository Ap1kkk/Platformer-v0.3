#pragma once

#include "IComponent.h"

class ITransform : public IComponent
{
public:
	ITransform() {}
	virtual ~ITransform() {}

	virtual void AddPosition(sf::Vector2f position) = 0;
	virtual void AddPosition(float x, float y) = 0;

	virtual void SetPosition(sf::Vector2f position) = 0;
	virtual void SetPosition(float x, float y) = 0;

	virtual void SetAngleInDeg(float angleInDeg) = 0;
	virtual void SetAngleInRad(float angleInRad) = 0;

	virtual float GetAngle() const = 0;
	virtual sf::Vector2f& GetPosition() = 0;
};

