#pragma once

#include "EventData.h"

class IEventListener
{
public:
	IEventListener() : listenerId(staticIdCounter++)
	{

	}
	virtual ~IEventListener()
	{

	}

	virtual void OnEventHappened(EventData& eventData) = 0;

protected:
	ListenerId listenerId;
private:
	static ListenerId staticIdCounter;
};

