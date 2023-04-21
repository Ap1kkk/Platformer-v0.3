#pragma once

#include "IEvent.h"

class OnEntityDestroyedEvent : public IEvent
{
public:
	OnEntityDestroyedEvent() : IEvent(typeid(OnEntityDestroyedEvent).name()) 
	{
		eventType = typeid(OnEntityDestroyedEvent).name();
	}

	static const EventType& GetType()
	{
		return eventType;
	}

private:
	static EventType eventType;
};

