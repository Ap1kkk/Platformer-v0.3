#pragma once

#include "IComponent.h"

#include "Debug.h"

class Health : public IComponent
{
public:

	void Awake() override
	{

	}



private:
	unsigned int health;
};

