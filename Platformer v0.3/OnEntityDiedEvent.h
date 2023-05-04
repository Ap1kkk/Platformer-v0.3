#pragma once

#include "IEvent.h"

class OnEntityDiedEvent : public IEvent
{
public:
	OnEntityDiedEvent()
	{
		eventType = typeid(OnEntityDiedEvent).name();
	}

	static const EventType& GetType()
	{
		return eventType;
	}

private:
	static EventType eventType;
};
