#pragma once

#include "SFML/Graphics.hpp"
#include "EventData.h"

struct EnemyMovementData : public UserEventData
{
	bool isRunning = false;
};