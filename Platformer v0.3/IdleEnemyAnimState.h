#pragma once

#include "AnimationState.h"
#include "EventListener.h"

class IdleEnemyAnimState : public AnimationState, public EventListener
{
public:
	IdleEnemyAnimState() : AnimationState(AnimationType::Idle) {}

	void OnStateEnter() override
	{
		SubscribeOnEvent(EventType::OnEnemyAttacked);
		SubscribeOnEvent(EventType::OnEnemyStartedRunning);
	}

	void OnStateExit() override
	{
		UnsubscribeFromEvent(EventType::OnEnemyAttacked);
		UnsubscribeFromEvent(EventType::OnEnemyStartedRunning);
	}

	void OnEventHappened(EventData& data) override
	{
		if (data.id == ownerId)
		{
			switch (data.eventType)
			{
			case EventType::OnEnemyStartedRunning:
			{
				ChangeState(AnimationType::Run);
				break;
			}
			case EventType::OnEnemyAttacked:
			{
				ChangeState(AnimationType::Attack);
				break;
			}
			}
		}
	}
};

