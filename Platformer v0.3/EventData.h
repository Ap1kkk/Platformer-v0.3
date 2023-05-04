#pragma once

#include <stdint.h>
#include "DataTypes.h"

struct UserEventData
{
	int i;
};

struct EventData
{
	EventData(EventType eventType) : eventType(eventType)
	{}

	unsigned int id;
	EventType eventType;

	UserEventData* userData;
};