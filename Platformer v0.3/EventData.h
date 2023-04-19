#pragma once

#include <stdint.h>
#include "DataTypes.h"

struct EventData
{
	EventData(EventType eventType) : eventType(eventType), owner_ptr(0)
	{}

	uintptr_t owner_ptr;
	EventType eventType;
};