#pragma once

#include "EventHandler.h"

#include "OnDestroyEvent.h"
#include "Debug.h"

class OnDestroyHandler : public EventHandler
{
public:
	OnDestroyHandler() : EventHandler(typeid(OnDestroyEvent).name()) {}

	//void HandleEvent(const EventData& eventData) override
	//{
	//	Debug::Log("Handler --");
	//}

};

