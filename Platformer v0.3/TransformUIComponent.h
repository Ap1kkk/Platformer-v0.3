#pragma once

//#include "IComponent.h"
#include "ITransform.h"
#include "Window.h"

class TransformUIComponent : public ITransform
{
public:
	TransformUIComponent();

	void UpdateUI() override;

	void AddPosition(sf::Vector2f position) override;
	void AddPosition(float x, float y) override;

	void SetPosition(sf::Vector2f position) override;
	void SetPosition(float x, float y) override;

	void SetAngleInDeg(float angleInDeg) override;
	void SetAngleInRad(float angleInRad) override;

	float GetAngle() const override;
	sf::Vector2f& GetPosition() override;

private:
	Window* window;
	sf::Vector2f viewCenter;

	sf::Vector2f initialPosition;
	sf::Vector2f position = { 0.f, 0.f };
	float angle = 0.f;
};

