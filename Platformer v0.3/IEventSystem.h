#pragma once

#include "EventData.h"
#include "IEntity.h"
#include "IComponent.h"

class IEventSystem
{
public:
	virtual const EventData& HandleEvent(const EventData& eventData) = 0;
	
	virtual void AddEventListener(EventType eventType, IEntity*) = 0;
	//virtual void AddEventListener(EventType eventType, IComponent*) = 0;

	virtual void RemoveEventListener(EventType eventType, IEntity*) = 0;
	//virtual void RemoveEventListener(EventType eventType, IComponent*) = 0;

};

