#pragma once

#include "EventData.h"

class EventHandler
{
public:
	EventHandler(const EventType& eventType) : eventType(eventType), handlerId(staticIdCounter++)
	{

	}
	virtual ~EventHandler()
	{

	}

	//virtual void HandleEvent(const EventData& eventData) = 0;

	const EventType& GetEventType() const { return eventType; }
	const HandlerId& GetHandlerId() const { return handlerId; }

protected:
	HandlerId handlerId;

private:
	EventType eventType;

	static HandlerId staticIdCounter;
};

