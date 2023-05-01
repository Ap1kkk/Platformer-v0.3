#pragma once

#include "IEvent.h"

class OnComponentDestroyedEvent : public IEvent
{
public:
	OnComponentDestroyedEvent()
	{
		eventType = typeid(OnComponentDestroyedEvent).name();
	}

	static const EventType& GetType()
	{
		return eventType;
	}

private:
	static EventType eventType;
};

