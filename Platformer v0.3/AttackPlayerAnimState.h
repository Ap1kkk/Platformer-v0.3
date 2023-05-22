#pragma once

#include "AnimationState.h"
#include "EventListener.h"

class AttackPlayerAnimState : public AnimationState, public EventListener
{
public:
	AttackPlayerAnimState() : AnimationState(AnimationType::Attack) {}

	void OnStateEnter() override
	{
		//SubscribeOnEvent(EventType::OnPlayerStartedRunning);
	}

	void OnStateExit() override
	{
		//UnsubscribeFromEvent(EventType::OnPlayerStartedRunning);
	}

	void OnEventHappened(EventData& data) override
	{
		if (data.eventType == EventType::OnPlayerStartedRunning)
		{
			ChangeState(AnimationType::Run);
		}
	}
};

