#pragma once

#include "IEvent.h"

class OnLevelSwitchEvent : public IEvent
{
public:
	OnLevelSwitchEvent()
	{
		eventType = typeid(OnLevelSwitchEvent).name();
	}

	static const EventType& GetType()
	{
		return eventType;
	}

private:
	static EventType eventType;
};

