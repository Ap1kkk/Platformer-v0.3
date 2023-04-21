#pragma once

#include <stdint.h>
#include "DataTypes.h"

struct UserEventData
{

};

struct EventData
{
	EventData(EventType eventType) : eventType(eventType)
	{}

	unsigned int id;
	EventType eventType;

	UserEventData userData;
};