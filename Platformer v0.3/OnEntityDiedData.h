#pragma once

#include "DataTypes.h"

struct OnEntityDiedData : public UserEventData
{
	EntityId entityId;
};