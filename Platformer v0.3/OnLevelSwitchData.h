#pragma once

#include "OnLevelSwitchEvent.h"

struct OnLevelSwitchData : public UserEventData
{
	GameLevels level;
};