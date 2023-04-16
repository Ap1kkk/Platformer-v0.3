#pragma once

#include "EventHandler.h"

#include "OnDestroyEvent.h"

class OnDestroyHandler : public EventHandler
{
public:
	OnDestroyHandler() : EventHandler(typeid(OnDestroyEvent).name()) {}
};

