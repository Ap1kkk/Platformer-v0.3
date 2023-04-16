#pragma once

#include "EventData.h"

class IEventSystem
{
public:
	virtual const EventData& HandleEvent(const EventData& eventData) = 0;
};

