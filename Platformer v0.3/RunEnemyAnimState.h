#pragma once

#include "AnimationState.h"
#include "EventListener.h"

class RunEnemyAnimState : public AnimationState, public EventListener
{
public:
	RunEnemyAnimState() : AnimationState(AnimationType::Run) {}

	void OnStateEnter() override
	{
		SubscribeOnEvent(EventType::OnEnemyAttacked);
		SubscribeOnEvent(EventType::OnEnemyStoppedRunning);
	}

	void OnStateExit() override
	{
		UnsubscribeFromEvent(EventType::OnEnemyAttacked);
		UnsubscribeFromEvent(EventType::OnEnemyStoppedRunning);
	}

	void OnEventHappened(EventData& data) override
	{
		if (data.id == ownerId)
		{
			switch (data.eventType)
			{
			case EventType::OnEnemyAttacked:
			{
				ChangeState(AnimationType::Attack);
				break;
			}
			case EventType::OnEnemyStoppedRunning:
			{
				ChangeState(AnimationType::Idle);
				break;
			}
			}
		}
		

	}
};


