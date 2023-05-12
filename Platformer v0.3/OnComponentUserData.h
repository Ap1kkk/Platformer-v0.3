#pragma once

#include "IComponent.h"
#include "DataTypes.h"

class IComponent;

struct ComponentUserData : public UserEventData
{
	IComponent* component;
};