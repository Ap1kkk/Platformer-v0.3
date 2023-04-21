#pragma once

#include <typeinfo>

#include "DataTypes.h"
#include "EventData.h"

#include "IEventSystem.h"

class IEvent
{
public:
	IEvent(const EventType& eventType) : eventType(eventType)
	{

	}
	virtual ~IEvent() {}

	static void Invoke(const EventData& eventData)
	{
		eventSystemPtr->HandleEvent(eventData);
	}

	static void SetEventSystem(IEventSystem* eventSystem)
	{
		eventSystemPtr = eventSystem;
	}

private:
	EventType eventType;
	static IEventSystem* eventSystemPtr;
};

