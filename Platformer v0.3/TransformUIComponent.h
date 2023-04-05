#pragma once

//#include "IComponent.h"
#include "ITransform.h"
#include "Window.h"

class TransformUIComponent : public ITransform
{
public:
	TransformUIComponent() 
	{
		SetComponentLayer(1);
		Debug::LogInfo("Created with id: " + std::to_string(componentId), typeid(*this).name());
	}

	//void Awake() override
	//{
	//	window = objectContext.window;
	//}

	void UpdateUI() override
	{
		auto view = objectContext.window->GetView();
		viewCenter = view.getCenter();
		//viewCenter = window->GetCentre();
		position = { viewCenter.x + initialPosition.x, viewCenter.y + initialPosition.y };
	}

	void AddPosition(sf::Vector2f position) override
	{
		this->initialPosition += position;
	}
	void AddPosition(float x, float y) override
	{
		this->initialPosition.x += x;
		this->initialPosition.y += y;
	}

	void SetPosition(sf::Vector2f position) override
	{
		this->initialPosition = position;
	}
	void SetPosition(float x, float y) override
	{
		this->initialPosition.x = x;
		this->initialPosition.y = y;
	}

	void SetAngleInDeg(float angleInDeg) override
	{
		angle = angleInDeg;
	}
	void SetAngleInRad(float angleInRad) override
	{
		angle = RADTODEG * angleInRad;
	}

	float GetAngle() const override
	{
		return angle;
	}
	sf::Vector2f& GetPosition() override
	{
		return position;
	}

private:
	Window* window;
	sf::Vector2f viewCenter;

	sf::Vector2f initialPosition;
	sf::Vector2f position = { 0.f, 0.f };
	float angle = 0.f;
};

