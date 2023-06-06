#pragma once

#include "AnimationState.h"
#include "EventListener.h"

#include "PlayerMovementData.h"

class JumpFallPlayerAnimState : public AnimationState, public EventListener
{
public:
	JumpFallPlayerAnimState() : AnimationState(AnimationType::JumpFall) {}

	void OnStateEnter() override
	{
		SubscribeOnEvent(EventType::OnPlayerLanded);
		SubscribeOnEvent(EventType::OnPlayerMovementCallback);
	}

	void OnStateExit() override
	{
		RefreshNonCyclicAnim();
		UnsubscribeFromEvent(EventType::OnPlayerLanded);
		UnsubscribeFromEvent(EventType::OnPlayerMovementCallback);
	}

	void OnEventHappened(EventData& data) override
	{
		if (data.eventType == EventType::OnPlayerLanded)
		{
			EventData eventData(EventType::OnPlayerMovementRequest);
			Event::Invoke(eventData);
		}
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
};