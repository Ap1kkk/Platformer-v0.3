#pragma once

#include "EventData.h"

class IEventListener
{
public:
	virtual void OnEventHappened(const EventData& eventData) = 0;
};

