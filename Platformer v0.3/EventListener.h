#pragma once

#include "EventSystem.h"

#include "IEventListener.h"
#include "IEventSystem.h"

#include "EventData.h"

#include "Debug.h"

#include "IEvent.h"

class EventListener : public IEventListener
{
public:
	virtual ~EventListener() 
	{
		Debug::LogWarning("Destructor", typeid(*this).name());
	}

	void SubscribeOnEvent(EventType eventType)
	{
		eventSystem->AddEventListener(eventType, this->listenerId, this);
	}
	void UnsubscribeFromEvent(EventType eventType)
	{
		eventSystem->RemoveEventListener(eventType, this->listenerId);
	}

	static void SetEventSystem(IEventSystem* eventSystemPtr) 
	{
		eventSystem = eventSystemPtr;
	}


private:

	static IEventSystem* eventSystem;
};

