#pragma once

//#include "IComponent.h"
#include "ITransform.h"
#include "Debug.h"

/// <summary>
/// Contains position and rotation of an object
/// Transforms synchronized with physic world
/// </summary>
class TransformComponent : public ITransform
{
public:
	TransformComponent();
	~TransformComponent() {}

	void AddPosition(sf::Vector2f position) override;
	void AddPosition(float x, float y) override;

	void SetPosition(sf::Vector2f position) override;
	void SetPosition(float x, float y) override;

	void SetAngleInDeg(float angleInDeg) override;
	void SetAngleInRad(float angleInRad) override;

	float GetAngle() const override;
	sf::Vector2f& GetPosition() override;

	//TODO добавить rotation
	//TODO добавить scale

private:
	sf::Vector2f position = { 0.f, 0.f };
	float angle = 0.f;
};