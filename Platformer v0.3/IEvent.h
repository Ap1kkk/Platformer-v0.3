#pragma once

#include <typeinfo>

#include "DataTypes.h"
#include "EventData.h"

#include "IEventSystem.h"

class Event
{
public:
	Event()
	{

	}
	virtual ~Event() {}

	static void Invoke(EventData& eventData)
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

