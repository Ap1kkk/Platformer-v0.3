#pragma once

#include "EventData.h"

class EventHandler
{
public:
	EventHandler(const EventType& eventType) : eventType(eventType)
	{

	}
	virtual ~EventHandler()
	{

	}

	virtual void HandleEvent(const EventData& eventData) = 0;

	const EventType& GetEventType() const { return eventType; }

private:
	EventType eventType;
};

