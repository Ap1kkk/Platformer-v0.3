#pragma once

#include "EventSystem.h"

#include "IEventListener.h"
#include "IEventSystem.h"

#include "Debug.h"

class EventListener : public IEventListener
{
public:

	template<class T>
	void SubscribeOnEvent()
	{
		eventSystem->AddEventListener(T::GetType(), this->listenerId, this);
	}
	template<class T>
	void UnsubscribeFromEvent()
	{
		eventSystem->RemoveEventListener(T::GetType(), this->listenerId, this);
	}

	//void OnEventHappened(const EventData& eventData) override
	//{
	//	Debug::Log("On event happened in listener");
	//}

	static void SetEventSystem(IEventSystem* eventSystemPtr) 
	{
		eventSystem = eventSystemPtr;
	}

private:
	static IEventSystem* eventSystem;
};

