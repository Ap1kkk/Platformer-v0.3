#pragma once

#include "IEvent.h"

class OnDestroyEvent : public IEvent
{
public:
	OnDestroyEvent() : IEvent(typeid(OnDestroyEvent).name()) {}
};

