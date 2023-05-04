#pragma once

#include "EventListener.h"
#include "OnEntityDiedEvent.h"

struct DamageData
{
	//TODO добавить шансы крита и так далее
	unsigned int value;
};

struct OnEntityDiedData : public UserEventData
{
	EntityId entityId;
};

class Damageble : public EventListener
{
public:
	Damageble(EntityId ownerId) : ownerId(ownerId)
	{
		SubscribeOnEvent<OnEntityDiedEvent>();
	}
	virtual ~Damageble() 
	{
		UnsubscribeFromEvent<OnEntityDiedEvent>();
	}

	virtual void TakeDamage(DamageData* damageData) = 0;

	void OnEventHappened(EventData& eventData)
	{
		if (eventData.eventType == OnEntityDiedEvent::GetType())
		{
			auto damageData = static_cast<OnEntityDiedData*>(eventData.userData);
			Debug::Log("Died");
			Debug::Log(damageData->entityId);
			OnEntityDied();
		}
	}

	virtual void OnEntityDied() = 0;

private:
	EntityId ownerId;
};

