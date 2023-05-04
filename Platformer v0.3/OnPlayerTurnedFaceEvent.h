#pragma once

#include "IEvent.h"

class OnPlayerTurnedFaceEvent : public IEvent
{
public:
	OnPlayerTurnedFaceEvent()
	{
		eventType = typeid(OnPlayerTurnedFaceEvent).name();
	}

	static const EventType& GetType()
	{
		return eventType;
	}

private:
	static EventType eventType;
};

