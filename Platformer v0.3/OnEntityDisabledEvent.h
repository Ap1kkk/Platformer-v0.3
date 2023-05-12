#pragma once

#include "IEvent.h"

class OnEntityDisabledEvent : public IEvent
{
public:
	OnEntityDisabledEvent()
	{
		eventType = typeid(OnEntityDisabledEvent).name();
	}

	static const EventType& GetType()
	{
		return eventType;
	}

private:
	static EventType eventType;
};

