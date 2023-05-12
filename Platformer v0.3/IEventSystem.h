#pragma once

#include "EventData.h"

#include "IEventListener.h"

class IEventSystem
{
public:
	virtual void HandleEvent(EventData& eventData) = 0;

	virtual void AddEventListener(EventType eventType, ListenerId listenerId, IEventListener* listener) = 0;
	virtual void RemoveEventListener(EventType eventType, ListenerId listenerId) = 0;
};

