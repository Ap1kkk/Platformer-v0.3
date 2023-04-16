#pragma once

#include <stdint.h>
#include "DataTypes.h"

struct EventData
{
	uintptr_t owner_ptr;
	EventType eventType;
};