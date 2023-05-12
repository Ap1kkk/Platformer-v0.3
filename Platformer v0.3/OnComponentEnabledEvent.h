#pragma once

#include "IEvent.h"

class OnComponentEnabledEvent : public IEvent
{
public:
	OnComponentEnabledEvent()
	{
		eventType = typeid(OnComponentEnabledEvent).name();
	}

	static const EventType& GetType()
	{
		return eventType;
	}

private:
	static EventType eventType;
};

