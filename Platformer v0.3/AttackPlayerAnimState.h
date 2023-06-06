#pragma once

#include "AnimationState.h"
#include "EventListener.h"

#include "PlayerMovementData.h"

class AttackPlayerAnimState : public AnimationState, public EventListener
{
public:
	AttackPlayerAnimState() : AnimationState(AnimationType::Attack) {}

	void OnStateEnter() override
	{
		SubscribeOnEvent(EventType::OnPlayerMovementCallback);
	}

	void OnStateExit() override
	{
		UnsubscribeFromEvent(EventType::OnPlayerMovementCallback);
		RefreshNonCyclicAnim();
	}

	void OnEventHappened(EventData& data) override
	{
		//if (data.eventType == EventType::OnPlayerStartedRunning)
		//{
		//	EventData eventData(EventType::OnPlayerMovementRequest);
		//	Event::Invoke(eventData);
		//}
		if (data.eventType == EventType::OnPlayerMovementCallback)
		{
			auto userData = static_cast<PlayerMovementData*>(data.userData);

			if (userData->isRunning)
			{
				if (userData->isSprinting)
				{
					ChangeState(AnimationType::Sprint);
				}
				else
				{
					ChangeState(AnimationType::Run);
				}
			}
			else
			{
				ChangeState(AnimationType::Idle);
			}
		}
	}

	void OnNonCyclicAnimEnded() override
	{
		EventData eventData(EventType::OnPlayerMovementRequest);
		Event::Invoke(eventData);
	}
};

