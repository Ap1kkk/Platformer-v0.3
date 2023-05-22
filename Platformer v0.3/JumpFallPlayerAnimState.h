#pragma once

#include "AnimationState.h"
#include "EventListener.h"

class JumpFallPlayerAnimState : public AnimationState, public EventListener
{
public:
	JumpFallPlayerAnimState() : AnimationState(AnimationType::JumpFall) {}

	void OnStateEnter() override
	{
		SubscribeOnEvent(EventType::OnPlayerLanded);
	}

	void OnStateExit() override
	{
		UnsubscribeFromEvent(EventType::OnPlayerLanded);
	}

	void OnEventHappened(EventData& data) override
	{
		if (data.eventType == EventType::OnPlayerLanded)
		{
			ChangeState(AnimationType::Idle);
		}
	}
};