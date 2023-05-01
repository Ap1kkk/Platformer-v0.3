#pragma once

#include "IEvent.h"

class OnTestEvent : public IEvent
{
public:
	OnTestEvent()
	{
		eventType = typeid(OnTestEvent).name();
	}

	static const EventType& GetType()
	{
		return eventType;
	}

private:
	static EventType eventType;
};

