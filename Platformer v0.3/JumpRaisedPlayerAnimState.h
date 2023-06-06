#pragma once

#include "AnimationState.h"
#include "EventListener.h"

class JumpRaisedPlayerAnimState : public AnimationState, public EventListener
{
public:
	JumpRaisedPlayerAnimState() : AnimationState(AnimationType::JumpRaise) {}

	void OnStateEnter() override
	{
		SubscribeOnEvent(EventType::OnPlayerJumpFall);
	}

	void OnStateExit() override
	{
		RefreshNonCyclicAnim();
		UnsubscribeFromEvent(EventType::OnPlayerJumpFall);
	}

	void OnEventHappened(EventData& data) override
	{
		if (data.eventType == EventType::OnPlayerJumpFall)
		{
			ChangeState(AnimationType::JumpFall);
		}
	}
};