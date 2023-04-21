#pragma once

#include "EventData.h"

#include "IEventListener.h"

class IEventSystem
{
public:
	virtual void HandleEvent(const EventData& eventData) = 0;
	
	//TODO поменять entityId на собственный id listener'a
	virtual void AddEventListener(EventType eventType, EntityId entityId, IEventListener* listener) = 0;
	//virtual void AddEventListener(EventType eventType, IComponent*) = 0;

	virtual void RemoveEventListener(EventType eventType, EntityId entityId) = 0;
	//virtual void RemoveEventListener(EventType eventType, IComponent*) = 0;

};

