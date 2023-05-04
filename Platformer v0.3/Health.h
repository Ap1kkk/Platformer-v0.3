#pragma once

#include "IComponent.h"

#include "Debug.h"

#include "Damageble.h"

#include "OnEntityDiedEvent.h"


const unsigned int START_HEALTH = 100;

class Health : public IComponent
{
public:
	virtual ~Health()
	{

	}

	void Awake() override
	{
		health = START_HEALTH;
	}

	void TakeDamage(DamageData* damageData)
	{
		Debug::Log("damage taken");
		ProcessDamage(damageData);
	}

	void OnDestroy() override
	{

	}

private:
	//TODO добавить учет всевозможных сопротивлений и так далее
	void ProcessDamage(DamageData* damageData)
	{
		health -= damageData->value;

		if (!IsAlive())
		{
			EventData eventData(OnEntityDiedEvent::GetType());

			auto userData = new OnEntityDiedData;
			userData->entityId = ownerId;
			eventData.userData = userData;

			OnEntityDiedEvent::Invoke(eventData);

			delete userData;
		}
	}

	bool IsAlive() { return health > 0; }

	unsigned int health;
};

