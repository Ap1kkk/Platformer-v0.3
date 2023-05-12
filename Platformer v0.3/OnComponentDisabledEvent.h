#pragma once

#include "IEvent.h"

class OnComponentDisabledEvent : public IEvent
{
public:
	OnComponentDisabledEvent()
	{
		eventType = typeid(OnComponentDisabledEvent).name();
	}

	static const EventType& GetType()
	{
		return eventType;
	}

private:
	static EventType eventType;
};

