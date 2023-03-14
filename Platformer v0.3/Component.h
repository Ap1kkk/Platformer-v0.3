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

	void EarlyUpdate() override {}
	void Update() override {}
	void LateUpdate() override {}

};