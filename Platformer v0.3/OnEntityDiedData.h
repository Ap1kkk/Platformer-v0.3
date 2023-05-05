#pragma once

#include "OnEntityDiedEvent.h"

struct OnEntityDiedData : public UserEventData
{
	EntityId entityId;
};