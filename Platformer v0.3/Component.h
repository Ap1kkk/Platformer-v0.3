#pragma once

#include "IComponent.h"
#include "Debug.h"

class Component : public IComponent
{
public:
	Component() {}
	virtual ~Component() 
	{
		//Debug::LogWarning("Destructor", typeid(*this).name());
	}

	void EarlyUpdate(float deltaTime) override {}
	void Update(float deltaTime) override {}
	void LateUpdate(float deltaTime) override {}
	void Draw(Window* window) override {}
};