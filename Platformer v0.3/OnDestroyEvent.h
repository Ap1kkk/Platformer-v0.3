#pragma once

#include "IEvent.h"

class OnDestroyEvent : public IEvent
{
public:
	OnDestroyEvent() : IEvent(typeid(OnDestroyEvent).name()) 
	{
		eventType = typeid(OnDestroyEvent).name();
	}

	static const EventType& GetType()
	{
		return eventType;
	}

private:
	static EventType eventType;
};

