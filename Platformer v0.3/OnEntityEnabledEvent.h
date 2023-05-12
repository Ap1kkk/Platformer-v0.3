#pragma once

#include "IEvent.h"

class OnEntityEnabledEvent : public IEvent
{
public:
	OnEntityEnabledEvent()
	{
		eventType = typeid(OnEntityEnabledEvent).name();
	}

	static const EventType& GetType()
	{
		return eventType;
	}

private:
	static EventType eventType;
};
