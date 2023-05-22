#pragma once

#include "DataTypes.h"


struct OnLevelSwitchData : public UserEventData
{
	GameLevels level;
};