#pragma once

#include <map>

#include "IEventSystem.h"
#include "EventHandler.h"

class EventSystem : public IEventSystem
{
public:

	const EventData& HandleEvent(const EventData& eventData)
	{
		return EventData();
	}

	template<class H>
	static void AddEventHandler()
	{
		auto handler = new H;
		handlers.emplace(std::make_pair(handler->GetEventType(), static_cast<EventHandler*>(handler))
	}

private:
	static std::multimap<EventType, EventHandler*> handlers;
};

