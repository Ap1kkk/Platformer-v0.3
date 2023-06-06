#pragma once

#include "AnimationState.h"
#include "EventListener.h"

#include "EnemyMovementData.h"

class AttackEnemyAnimState : public AnimationState, public EventListener
{
public:
	AttackEnemyAnimState() : AnimationState(AnimationType::Attack) {}

	void OnStateEnter() override
	{
		SubscribeOnEvent(EventType::OnEnemyMovementCallback);

	}

	void OnStateExit() override
	{
		RefreshNonCyclicAnim();
		UnsubscribeFromEvent(EventType::OnEnemyMovementCallback);

	}

	void OnEventHappened(EventData& data) override
	{
		if (data.eventType == EventType::OnEnemyMovementCallback)
		{
			if (data.id == ownerId)
			{
				auto userData = static_cast<EnemyMovementData*>(data.userData);

				if (userData->isRunning)
				{
					ChangeState(AnimationType::Run);
				}
				else
				{
					ChangeState(AnimationType::Idle);
				}
			}
		}
	}

	void OnNonCyclicAnimEnded() override
	{
		EventData eventData(EventType::OnEnemyMovementRequest);
		eventData.id = ownerId;
		Event::Invoke(eventData);
	}
};