#pragma once

#include <typeinfo>

#include "DataTypes.h"
#include "EventData.h"

#include "IEventSystem.h"

class IEvent
{
public:
	IEvent()
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
	static IEventSystem* eventSystemPtr;
};

