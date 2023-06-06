#pragma once

#include "SFML/Graphics.hpp"
#include "EventData.h"

struct PlayerMovementData : public UserEventData
{
	bool isRunning = false;
	bool isSprinting = false;
};