#pragma once

#include <map>

#include "IEventSystem.h"
#include "EventHandler.h"

#include "Debug.h"

class EventSystem : public IEventSystem
{
public:

	const EventData& HandleEvent(const EventData& eventData) override
	{
		Debug::Log("Handle event from event system");

		for (auto itr = entityHandlers.lower_bound(eventData.eventType); itr != entityHandlers.upper_bound(eventData.eventType); ++itr)
		{
			//itr->second.second->HandleEvent(eventData);
		}

		return EventData();
	}

	void AddEventListener(EventType eventType, IEntity*) override
	{

	}
	//virtual void AddEventListener(EventType eventType, IComponent*) = 0;

	void RemoveEventListener(EventType eventType, IEntity*) override
	{

	}
	//virtual void RemoveEventListener(EventType eventType, IComponent*) = 0;

private:
	//static std::multimap<EventType, EventHandler*> handlers;
	static std::multimap<EventType, std::pair<EntityId, IEntity*>> entityHandlers;
	static std::multimap<EventType, std::pair<ComponentId, IComponent*>> componentHandlers;
};

