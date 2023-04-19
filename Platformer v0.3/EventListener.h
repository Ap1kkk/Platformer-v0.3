#pragma once

#include "EventData.h"
#include "EventSystem.h"

#include "IEntity.h"
#include "IComponent.h"

#include "IEventListener.h"
#include "IEventSystem.h"

#include "OnDestroyEvent.h"

#include "Debug.h"

class EventListener : public IEventListener
{
public:

	template<class T>
	void SubscribeOnEvent(IEntity* entity)
	{
		eventSystem->AddEventListener(T::GetType(), entity);
	}
	template<class T>
	void UnsubscribeFromEvent(IEntity* entity)
	{
		eventSystem->RemoveEventListener(T::GetType(), entity);
	}

	void OnEventHappened(const EventData& eventData) override
	{
		Debug::Log("On event happened in listener");
	}

	static void SetEventSystem(IEventSystem* eventSystemPtr) 
	{
		eventSystem = eventSystemPtr;
	}

private:
	static IEventSystem* eventSystem;
};

